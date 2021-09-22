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

![web-page-1](https://user-images.githubusercontent.com/6020549/134284813-1922b62a-c03e-4842-a46d-5395cbf89f3a.jpg)
![web-page-2](https://user-images.githubusercontent.com/6020549/134284820-baa01fb7-42ee-4a80-93cf-02969fa1d4c6.jpg)
![web-page-3](https://user-images.githubusercontent.com/6020549/134284824-6a8d9b7e-5d40-4c89-8858-3050e7f6bbff.jpg)
![web-page-4](https://user-images.githubusercontent.com/6020549/134284827-f1e8ca4e-2d42-4ea7-b418-517abbf3e861.jpg)
![web-page-5](https://user-images.githubusercontent.com/6020549/134284835-e9b83f12-b362-44a5-875d-932cc66ef319.jpg)

# HTML Header
You can set your HTML Header to html/head.html.

