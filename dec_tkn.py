import json
import base64
import sys

def decode_string(encoded_text, file_path):
    decoded_text = base64.b64decode(encoded_text).decode('utf-8')
    data = json.loads(decoded_text)
    str1 = data["str1"]
    str2 = data["str2"]
    text = data["text"]
    with open(file_path, 'w') as file:
        file.write(text)
    return str1, str2

if __name__ == "__main__":
    length = len(sys.argv)
    print(f"Length: {length}")
    if length < 2:
        print("Usage: python3 dec_tkn.py <IA_SECRETS> <PEM_KEY file>")
        sys.exit(1)
    #encoded_text = sys.argv[1]
    #file_path = sys.argv[2]
    #str1, str2 = decode_string(encoded_text, file_path)
    #print(f"New string 1: {str1}")
    #print(f"New string 2: {str2}")
