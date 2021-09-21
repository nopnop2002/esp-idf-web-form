/* HTTP Server Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs.h"
#include "esp_http_server.h"

#include "http_server.h"

static const char *TAG = "HTTP";

extern QueueHandle_t xQueueHttp;

#define STORAGE_NAMESPACE "storage"

esp_err_t save_key_value(char * key, char * value)
{
	nvs_handle_t my_handle;
	esp_err_t err;

	// Open
	err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK) return err;

	// Write
	err = nvs_set_str(my_handle, key, value);
	if (err != ESP_OK) return err;

	// Commit written value.
	// After setting any values, nvs_commit() must be called to ensure changes are written
	// to flash storage. Implementations may write to storage at other times,
	// but this is not guaranteed.
	err = nvs_commit(my_handle);
	if (err != ESP_OK) return err;

	// Close
	nvs_close(my_handle);
	return ESP_OK;
}

esp_err_t load_key_value(char * key, char * value, size_t size)
{
	nvs_handle_t my_handle;
	esp_err_t err;

	// Open
	err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK) return err;

	// Read
	size_t _size = size;
	err = nvs_get_str(my_handle, key, value, &_size);
	ESP_LOGI(TAG, "nvs_get_str err=%d", err);
	//if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) return err;
	if (err != ESP_OK) return err;
	ESP_LOGI(TAG, "err=%d key=[%s] value=[%s] _size=%d", err, key, value, _size);

	// Close
	nvs_close(my_handle);
	//return ESP_OK;
	return err;
}

/* HTTP ROOT handler */
static esp_err_t root_get_handler(httpd_req_t *req)
{
	ESP_LOGI(TAG, "root_get_handler req->uri=[%s]", req->uri);
	char key[64];
	char parameter[128];
	esp_err_t err;

	// Send HTML header
	httpd_resp_sendstr_chunk(req, "<!DOCTYPE html><html><body>");
	httpd_resp_sendstr_chunk(req, "<h1>WEB Form Demo using ESP-IDF</h1>");

	httpd_resp_sendstr_chunk(req, "<h2>input text</h2>");
	httpd_resp_sendstr_chunk(req, "<form method=\"get\" action=\"/submit1\">");
	httpd_resp_sendstr_chunk(req, "input1: <input type=\"text\" name=\"input1\">");
	httpd_resp_sendstr_chunk(req, "<br>");
	httpd_resp_sendstr_chunk(req, "input2: <input type=\"text\" name=\"input2\">");
	httpd_resp_sendstr_chunk(req, "<br>");
	httpd_resp_sendstr_chunk(req, "<input type=\"submit\" value=\"Submit1\">");
	httpd_resp_sendstr_chunk(req, "</form><br>");

	strcpy(key, "submit1");
	err = load_key_value(key, parameter, sizeof(parameter));
	ESP_LOGI(TAG, "%s=%d", key, err);
	if (err == ESP_OK) {
		ESP_LOGI(TAG, "parameter=[%s]", parameter);
		httpd_resp_sendstr_chunk(req, key);
		httpd_resp_sendstr_chunk(req, ":");
		httpd_resp_sendstr_chunk(req, parameter);
	}

	httpd_resp_sendstr_chunk(req, "<hr>");

	httpd_resp_sendstr_chunk(req, "<h2>input text</h2>");
	httpd_resp_sendstr_chunk(req, "<form method=\"get\" action=\"/submit2\">");
	httpd_resp_sendstr_chunk(req, "input3: <input type=\"text\" name=\"input3\">");
	httpd_resp_sendstr_chunk(req, "<br>");
	httpd_resp_sendstr_chunk(req, "input4: <input type=\"text\" name=\"input4\">");
	httpd_resp_sendstr_chunk(req, "<br>");
	httpd_resp_sendstr_chunk(req, "<input type=\"submit\" value=\"Submit2\">");
	httpd_resp_sendstr_chunk(req, "</form><br>");

	strcpy(key, "submit2");
	err = load_key_value(key, parameter, sizeof(parameter));
	ESP_LOGI(TAG, "%s=%d", key, err);
	if (err == ESP_OK) {
		ESP_LOGI(TAG, "parameter=[%s]", parameter);
		httpd_resp_sendstr_chunk(req, key);
		httpd_resp_sendstr_chunk(req, ":");
		httpd_resp_sendstr_chunk(req, parameter);
	}

	httpd_resp_sendstr_chunk(req, "<hr>");

	httpd_resp_sendstr_chunk(req, "<h2>input checkbox</h2>");
	httpd_resp_sendstr_chunk(req, "<form method=\"get\" action=\"/submit3\">");
	httpd_resp_sendstr_chunk(req, "<input type=\"checkbox\" name=\"check1\">RED");
	httpd_resp_sendstr_chunk(req, "<input type=\"checkbox\" name=\"check2\">GREEN");
	httpd_resp_sendstr_chunk(req, "<input type=\"checkbox\" name=\"check3\">BLUE");
	httpd_resp_sendstr_chunk(req, "<br>");
	httpd_resp_sendstr_chunk(req, "<input type=\"submit\" value=\"Submit3\">");
	httpd_resp_sendstr_chunk(req, "</form><br>");

	strcpy(key, "submit3");
	err = load_key_value(key, parameter, sizeof(parameter));
	ESP_LOGI(TAG, "%s=%d", key, err);
	if (err == ESP_OK) {
		ESP_LOGI(TAG, "parameter=[%s]", parameter);
		httpd_resp_sendstr_chunk(req, key);
		httpd_resp_sendstr_chunk(req, ":");
		httpd_resp_sendstr_chunk(req, parameter);
	}

	httpd_resp_sendstr_chunk(req, "<hr>");

	httpd_resp_sendstr_chunk(req, "<h2>input radio</h2>");
	httpd_resp_sendstr_chunk(req, "<form method=\"get\" action=\"/submit4\">");
	httpd_resp_sendstr_chunk(req, "<input type=\"radio\" name=\"radio1\">RED");
	httpd_resp_sendstr_chunk(req, "<input type=\"radio\" name=\"radio2\">GREEN");
	httpd_resp_sendstr_chunk(req, "<input type=\"radio\" name=\"radio3\">BLUE");
	httpd_resp_sendstr_chunk(req, "<br>");
	httpd_resp_sendstr_chunk(req, "<input type=\"submit\" value=\"Submit4\">");
	httpd_resp_sendstr_chunk(req, "</form><br>");

	strcpy(key, "submit4");
	err = load_key_value(key, parameter, sizeof(parameter));
	ESP_LOGI(TAG, "%s=%d", key, err);
	if (err == ESP_OK) {
		ESP_LOGI(TAG, "parameter=[%s]", parameter);
		httpd_resp_sendstr_chunk(req, key);
		httpd_resp_sendstr_chunk(req, ":");
		httpd_resp_sendstr_chunk(req, parameter);
	}

	/* Send remaining chunk of HTML file to complete it */
	httpd_resp_sendstr_chunk(req, "</body></html>");

	/* Send empty chunk to signal HTTP response completion */
	httpd_resp_sendstr_chunk(req, NULL);

	return ESP_OK;
}

/* HTTP SUMBIT handler */
static esp_err_t root_submit1_handler(httpd_req_t *req)
{
	ESP_LOGI(TAG, "root_submit1_handler req->uri=[%s]", req->uri);
	URL_t urlBuf;
	strcpy(urlBuf.url, "submit1");
	strcpy(urlBuf.parameter, &req->uri[9]);
	if (xQueueSend(xQueueHttp, &urlBuf, portMAX_DELAY) != pdPASS) {
		ESP_LOGE(TAG, "xQueueSend Fail");
	}

	/* Redirect onto root to see the updated file list */
	httpd_resp_set_status(req, "303 See Other");
	httpd_resp_set_hdr(req, "Location", "/");
#ifdef CONFIG_EXAMPLE_HTTPD_CONN_CLOSE_HEADER
	httpd_resp_set_hdr(req, "Connection", "close");
#endif
	httpd_resp_sendstr(req, "post successfully");
	return ESP_OK;
}

static esp_err_t root_submit2_handler(httpd_req_t *req)
{
	ESP_LOGI(TAG, "root_submit2_handler req->uri=[%s]", req->uri);
	URL_t urlBuf;
	strcpy(urlBuf.url, "submit2");
	strcpy(urlBuf.parameter, &req->uri[9]);
	if (xQueueSend(xQueueHttp, &urlBuf, portMAX_DELAY) != pdPASS) {
		ESP_LOGE(TAG, "xQueueSend Fail");
	}

	/* Redirect onto root to see the updated file list */
	httpd_resp_set_status(req, "303 See Other");
	httpd_resp_set_hdr(req, "Location", "/");
#ifdef CONFIG_EXAMPLE_HTTPD_CONN_CLOSE_HEADER
	httpd_resp_set_hdr(req, "Connection", "close");
#endif
	httpd_resp_sendstr(req, "post successfully");
	return ESP_OK;
}

static esp_err_t root_submit3_handler(httpd_req_t *req)
{
	ESP_LOGI(TAG, "root_submit3_handler req->uri=[%s]", req->uri);
	URL_t urlBuf;
	strcpy(urlBuf.url, "submit3");
	strcpy(urlBuf.parameter, &req->uri[9]);
	if (xQueueSend(xQueueHttp, &urlBuf, portMAX_DELAY) != pdPASS) {
		ESP_LOGE(TAG, "xQueueSend Fail");
	}

	/* Redirect onto root to see the updated file list */
	httpd_resp_set_status(req, "303 See Other");
	httpd_resp_set_hdr(req, "Location", "/");
#ifdef CONFIG_EXAMPLE_HTTPD_CONN_CLOSE_HEADER
	httpd_resp_set_hdr(req, "Connection", "close");
#endif
	httpd_resp_sendstr(req, "post successfully");
	return ESP_OK;
}

static esp_err_t root_submit4_handler(httpd_req_t *req)
{
	ESP_LOGI(TAG, "root_submit4_handler req->uri=[%s]", req->uri);
	URL_t urlBuf;
	strcpy(urlBuf.url, "submit4");
	strcpy(urlBuf.parameter, &req->uri[9]);
	if (xQueueSend(xQueueHttp, &urlBuf, portMAX_DELAY) != pdPASS) {
		ESP_LOGE(TAG, "xQueueSend Fail");
	}

	/* Redirect onto root to see the updated file list */
	httpd_resp_set_status(req, "303 See Other");
	httpd_resp_set_hdr(req, "Location", "/");
#ifdef CONFIG_EXAMPLE_HTTPD_CONN_CLOSE_HEADER
	httpd_resp_set_hdr(req, "Connection", "close");
#endif
	httpd_resp_sendstr(req, "post successfully");
	return ESP_OK;
}



/* Function to start the web server */
esp_err_t start_server(const char *base_path, int port)
{
	httpd_handle_t server = NULL;
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	config.server_port = port;

	/* Use the URI wildcard matching function in order to
	 * allow the same handler to respond to multiple different
	 * target URIs which match the wildcard scheme */
	config.uri_match_fn = httpd_uri_match_wildcard;

	ESP_LOGI(TAG, "Starting HTTP Server on port: '%d'", config.server_port);
	if (httpd_start(&server, &config) != ESP_OK) {
		ESP_LOGE(TAG, "Failed to start file server!");
		return ESP_FAIL;
	}

	/* URI handler for ROOT */
	httpd_uri_t root_get = {
		.uri	   = "/",	// Match all URIs of type /path/to/file
		.method    = HTTP_GET,
		.handler   = root_get_handler,
		//.user_ctx  = server_data	// Pass server data as context
	};
	httpd_register_uri_handler(server, &root_get);

	/* URI handler for SUMBIT */
	httpd_uri_t root_submit1 = {
		.uri	   = "/submit1",
		.method    = HTTP_GET,
		.handler   = root_submit1_handler,
		//.user_ctx  = server_data	// Pass server data as context
	};
	httpd_register_uri_handler(server, &root_submit1);

	httpd_uri_t root_submit2 = {
		.uri	   = "/submit2",
		.method    = HTTP_GET,
		.handler   = root_submit2_handler,
		//.user_ctx  = server_data	// Pass server data as context
	};
	httpd_register_uri_handler(server, &root_submit2);

	httpd_uri_t root_submit3 = {
		.uri	   = "/submit3",
		.method    = HTTP_GET,
		.handler   = root_submit3_handler,
		//.user_ctx  = server_data	// Pass server data as context
	};
	httpd_register_uri_handler(server, &root_submit3);

	httpd_uri_t root_submit4 = {
		.uri	   = "/submit4",
		.method    = HTTP_GET,
		.handler   = root_submit4_handler,
		//.user_ctx  = server_data	// Pass server data as context
	};
	httpd_register_uri_handler(server, &root_submit4);


	return ESP_OK;
}


void http_server_task(void *pvParameters)
{
	char *task_parameter = (char *)pvParameters;
	ESP_LOGI(TAG, "Start task_parameter=%s", task_parameter);
	char url[64];
	sprintf(url, "http://%s:%d", task_parameter, CONFIG_WEB_PORT);

	// Start Server
	ESP_LOGI(TAG, "Starting server on %s", url);
	ESP_ERROR_CHECK(start_server("/spiffs", CONFIG_WEB_PORT));
	
	URL_t urlBuf;
	while(1) {
		// Waiting for submit
		if (xQueueReceive(xQueueHttp, &urlBuf, portMAX_DELAY) == pdTRUE) {
			ESP_LOGI(TAG, "url=%s", urlBuf.url);
			ESP_LOGI(TAG, "parameter=%s", urlBuf.parameter);

			// save key & value to NVS
			esp_err_t err = save_key_value(urlBuf.url, urlBuf.parameter);
			if (err != ESP_OK) {
				ESP_LOGE(TAG, "Error (%s) saving to NVS", esp_err_to_name(err));
			}

			// load key & value from NVS
			err = load_key_value(urlBuf.url, urlBuf.parameter, sizeof(urlBuf.parameter));
			if (err != ESP_OK) {
				ESP_LOGE(TAG, "Error (%s) loading to NVS", esp_err_to_name(err));
			}
		}
	}

	// Never reach here
	ESP_LOGI(TAG, "finish");
	vTaskDelete(NULL);
}
