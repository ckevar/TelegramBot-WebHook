# telegramBot-WebHook
This is an webserver to be used as a webhook for a Telegram Bot. It means it uses tlsv1.2 from openssl libraries. 
Since this is a self-signed HTTP webserver, the certificate has to be uploaded manually. You will find furthere information below.

## Getting started
### First step:
After running make, you are ready to go.
### Second Step in Terminal:
```javascript
var s = "JavaScript syntax highlighting";
alert(s);
```
- ``` bash
cd https-webserver/server/sslkeys
- ```bash
chmod +x genkeys.sh˘˘ 
- ˘˘./genkeys.sh˘˘, this will generate public and private keys
- ˘˘cd ../˘˘, server folder
- ˘˘sudo ./main˘˘ 
## Reqs
- openssl (libssl-dev)

