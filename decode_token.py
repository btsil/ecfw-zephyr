import json
import base64
import sys
import time
import jwt
import requests
import os

def decode_token(token_file):
    #with open(token_file, 'r') as file:
        #encoded_text = file.read()
    decoded_text = base64.b64decode(token_file).decode('utf-8')
    data = json.loads(decoded_text)
    APP_ID = data["str1"]
    INSTALLATION_ID = data["str2"]
    PEM = data["text"]

    now = int(time.time())
    iat = now - 60
    exp = now + 60
    header = {"alg": "RS256", "typ": "JWT"}
    payload = {"iat": iat, "exp": exp, "iss": APP_ID}
    jwt_token = jwt.encode(payload, PEM, algorithm="RS256", headers=header)

    url = f"https://api.github.com/app/installations/{INSTALLATION_ID}/access_tokens"
    headers = {
        "Authorization": f"Bearer {jwt_token}",
        "Accept": "application/vnd.github+json",
        "X-GitHub-Api-Version": "2022-11-28"
    }

    response = requests.post(url, headers=headers)
    INSTALLATION_ACCESS_TOKEN = response.json()['token']
    return INSTALLATION_ACCESS_TOKEN


if __name__ == "__main__":
    #token = os.environ['IA_SECRETS']
    token = sys.argv[1]
    access_token = decode_token(token)
    print(access_token)
