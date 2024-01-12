set -o pipefail

APP_ID=$1           # App ID as first argument
PEM=$2              # private key file as second argument
INSTALLATION_ID=$3  # instllation ID
 
now=$(date +%s)
iat=$((${now} - 60))
exp=$((${now} + 60))
b64enc() { openssl base64 | tr -d '=' | tr '/+' '_-' | tr -d '\n'; }
header_json='{"typ":"JWT","alg":"RS256"}'
header=$( echo -n "${header_json}" | b64enc )
payload_json='{"iat":'"${iat}"',"exp":'"${exp}"',"iss":'"${APP_ID}"'}'
payload=$( echo -n "${payload_json}" | b64enc )
header_payload="${header}"."${payload}"
signature=$(openssl dgst -sha256 -sign ${PEM} <(echo -n "${header_payload}") | b64enc )
JWT="${header_payload}"."${signature}"
INSTALLATION_ACCESS_TOKEN=$(curl -s -L \
            -X POST \
            -H "Accept: application/vnd.github+json" \
            -H "Authorization: Bearer ${JWT}" \
            -H "X-GitHub-Api-Version: 2022-11-28" https://api.github.com/app/installations/${INSTALLATION_ID}/access_tokens | jq -r '.token')
echo $INSTALLATION_ACCESS_TOKEN