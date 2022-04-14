# telegramBot-WebHook
This is an webserver to be used as a webhook for a Telegram Bot. It means it uses tlsv1.2 from openssl libraries. 
Since this is a self-signed HTTP webserver, the certificate has to be uploaded manually. You will find furthere information below.

## Getting started
### First step:
After running make, you are ready to go.
### Second Step in Terminal:

- Go to sslkey folder
``` bash
$ cd https-webserver/server/sslkeys
```
- Open the generator bash to edit
``` bash
$ nano genkeys.sh
``` 
- Edit the generator bash with your information. In the openssl line, set your public IP as CN
``` bash
openssl req -newkey rsa:2048 -sha256 -nodes -keyout my-ssl-private.key\
  -x509 -days 365 -out my-ssl-public.pem\
  -subj "/C=US/ST=New York/L=Brooklyn/O=bot company/CN=<Public IP>"
``` 
- On the same file. In the line curl, your public IP and your telegram Bot TOKEN are needed. This is used to upload your public key to the telegram api server:
``` bash
curl -F "url=https://<IPublic IP>/" -F "certificate=@sslkeys/my-ssl-public.pem"\
  https://api.telegram.org/bot<TELEGRAM BOT API TOKEN>/setWebhook
```
- Add execution feature to the file
``` bash
$ chmod +x genkeys.sh
```
- Generate the private and public keys and upload your public to the telegram server
``` bash
$ ./genkeys.sh
```
- Go back to the server folder
``` bash
$ cd ../
``` 
- (Optional) start a screen
``` bash
$ screen
```
- On the new screen created, run the server
``` bash
$ sudo ./main
```

## Reqs
- openssl (libssl-dev)
- (optional) screen
