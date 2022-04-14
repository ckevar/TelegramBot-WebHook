# set CN your public IP for telegram purposes
openssl req -newkey rsa:2048 -sha256 -nodes -keyout my-ssl-private.key -x509 -days 365 -out my-ssl-public.pem -subj "/C=US/ST=New York/L=Brooklyn/O=cibot company/CN=<Public IP or Common Name>"
# upload certification
# DOCUMENTATION FOR TELEGRAM: https://core.telegram.org/bots/webhooks#how-do-i-set-a-webhook-for-either-type
curl -F "url=https://<IPublic IP>/" -F "certificate=@sslkeys/my-ssl-public.pem" https://api.telegram.org/bot<TELEGRAM API TOKEN>/setWebhook
