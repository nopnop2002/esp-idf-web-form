# esp-idf-web-form
WEB Form example for ESP-IDF.   
ESP-IDF contains a lot of sample code, but there is no sample to create FORM on the WEB and input data from FORM.   
No library other than ESP-IDF is required to read the data from the WEB page.   

I referred [here](https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/).   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-web-form
cd esp-idf-web-form
idf.py set-target esp32
idf.py menuconfig
idf.py flash monitor
```


# Configuration
Set the following items using menuconfig.

![config-main](https://user-images.githubusercontent.com/6020549/134126480-a1455518-e6c8-4897-a1e2-aec5dda50168.jpg)
![config-app](https://user-images.githubusercontent.com/6020549/134126500-cc609a2c-cc74-4eca-a5ad-359abe8cbe26.jpg)

## Wifi Setting

![config-wifi-1](https://user-images.githubusercontent.com/6020549/134127430-e55a9a9f-e3db-4766-a806-687ba58bad9a.jpg)

You can use the mDNS hostname instead of the IP address.   
- esp-idf V4.3 or earlier   
 You will need to manually change the mDNS strict mode according to [this](https://github.com/espressif/esp-idf/issues/6190) instruction.   
- esp-idf V4.4 or later  
 If you set CONFIG_MDNS_STRICT_MODE = y in sdkconfig.default, the firmware will be built with MDNS_STRICT_MODE = 1.

![config-wifi-2](https://user-images.githubusercontent.com/6020549/134127158-892fac80-d123-4fd8-af16-f0b234a0efba.jpg)

You can use static IP.   
![config-wifi-3](https://user-images.githubusercontent.com/6020549/134127193-8bffe977-b4b8-4178-9810-06c99414055f.jpg)

## HTTP Server Setting
![config-http](https://user-images.githubusercontent.com/6020549/134127228-dbcdca4c-ea3a-45c8-82d2-5dbced108fe3.jpg)


# How to use
Open your brouser, and put address in address bar.   
You can use the mDNS hostname instead of the IP address.   
Default mDNS name is esp32-server.local.   
Input text/checkbox/radio and submit.   
The read data is saved in the NVS area.   
You can clear the NVS area with this command:   
```
idf.py erase_flash
```
![web-page-1](https://user-images.githubusercontent.com/6020549/134334596-8cc6f1c8-a653-4826-b7b2-8ee79049b31f.jpg)
![web-page-2](https://user-images.githubusercontent.com/6020549/134334601-1be21151-0eb1-4fb0-8d6d-20eeb9dfa06a.jpg)
![web-page-3](https://user-images.githubusercontent.com/6020549/134334603-c464bc43-264c-46b6-bac4-3c0aac1cd11f.jpg)
![web-page-4](https://user-images.githubusercontent.com/6020549/134334607-e767c44b-29b5-4ac2-b3b2-e7f44e24d82c.jpg)
![web-page-5](https://user-images.githubusercontent.com/6020549/134334608-46eedaa9-6e89-4458-ad4a-8df08c48fc9a.jpg)

# HTML Header
You can set your HTML Header to html/head.html.

