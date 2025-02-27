
#ifdef __cplusplus
extern "C" {
#endif
#include "driver/uart.h"

#define TestBit(A, pos) (A[(pos) / 32] & (1 << ((pos) % 32)))

typedef struct
{
    uint8_t event;
    uint32_t length;
    char *bufferPtr;
} appl_message_t;

typedef struct
{
  uint32_t TAG_ID;
  uint8_t length;
  uint8_t *bufferPtr;
} caniot_message_t;



/***************************************************************************
* @name      caniotBox_init 
* @brief     init caniot box application.
*
* @attention 1. This API should be called at first, before all functions
* @param     void
*
* @return    void
*****************************************************************************/
extern void caniotBox_init(void);
/***************************************************************************
* @name      serialOutput_configure
* @brief     init serial out with the given baudRate.
*
* @attention 1. This API should be called after caniotBox_init
* @param     void
*
* @return    void
*****************************************************************************/
extern esp_err_t serialOutput_configure(int baudRate);
/***************************************************************************
* @name      serialOutput_sendString
* @brief     Prints data to the serial port as human-readable ASCII text.
*
* @attention 1. This API should be called after caniotBox_init and serialOutput_configure
* @param     fmt : specific the formated string
*
* @return    esp_err_t
*****************************************************************************/
extern esp_err_t serialOutput_sendString(const char *fmt, ...);
/***************************************************************************
* @name      serialOutput_send_buffer_hex
* @brief     Prints data to the serial port as human-readable ASCII text.
*
* @attention 1. This API should be called after caniotBox_init and serialOutput_configure
* @param     tag : tag to be printed fo this hex buffer
*            bufferOutput : buffer pointer contents the data
*            length: data length to be send
*
* @return    esp_err_t
*****************************************************************************/
extern esp_err_t serialOutput_send_buffer_hex(const char *tag,const char *color, const void *bufferOutput, uint16_t length);
/***************************************************************************
* @name      serialOutput_sendRaw
* @brief     Prints given data to the serial port with a fixed length.
*
* @attention 1. This API should be called after caniotBox_init and serialOutput_configure
* @param     bufferOutput : buffer pointer contents the data
*            length: data length to be send
*
* @return    esp_err_t
*****************************************************************************/
extern esp_err_t serialOutput_sendRaw(char * bufferOutput, int length);
/* define for using with serialOutput_sendString*/
#define END_BRACKET		"\x1b[32;1m]\x1b[0m"
#define START_BRACKET	"\x1b[32;1m[\x1b[0m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_RED		  "\x1b[31m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_CYAN		"\x1b[36m"
#define HOME_SCREEN		"\x1b[H"
/***************************************************************************
* @name      Kline_uart_init
* @brief     Install UART Kline driver and set the UART to the given configuration. .
*
* @attention 1. This API should be called after caniotBox_init
* @param    - uart_config_t : UART configuration parameters (see uart_types.h)
*
* @return    uart_port_t UART port number, can be UART_NUM_0 ~ (UART_NUM_MAX -1)
*****************************************************************************/
uart_port_t extern  Kline_uart_init(uart_config_t* uart_config);
/***************************************************************************
* @name      startAppl_UdsFlash
* @brief     Install UART Kline driver and set the UART to the given configuration. .
*
* @attention 1. This API should be called after caniotBox_init
* @param    - uart_config_t : UART configuration parameters (see uart_types.h)
*
* @return    uart_port_t UART port number, can be UART_NUM_0 ~ (UART_NUM_MAX -1)
*****************************************************************************/
extern void  startAppl_UdsFlash(const char * filename,const char * uds_name);
/***************************************************************************
* @name      send_to_caniot_appl
* @brief     send data to caniot application .
*
* @attention 1. This API should be called after caniotBox_init
* @param    receiveData : buffer pointer contents the data
*            length: data length to be send Max 64 bytes
*
* @return    uart_port_t UART port number, can be UART_NUM_0 ~ (UART_NUM_MAX -1)
*****************************************************************************/
extern void send_to_caniot_appl(char *receiveData, size_t length);
/***************************************************************************
* @name      prepare_caniot_data
* @brief     convert given caniot_message  to a caniot message .
*
* @attention 1. This API should be called after caniotBox_init
* @param     caniot_message_t : structur content the frame information
*            caniot_data_length : data bytes length 
*
* @return   DLC 
*****************************************************************************/
extern uint8_t *prepare_caniot_data(caniot_message_t *message_arg, uint8_t *caniot_data_length);
/*************************************************************************
* @brief     read file from path defined by fileNames
* @name      appl_read_file_sync 
* @param     appl_messagefile : structur content the file data
*            fileName : string of file name 
*            openType :  "r" or "rb"
* @return   bool : true if reading file was ok
***************************************************************************/
extern bool appl_read_file_sync(appl_message_t *appl_messagefile, char *fileName,const char*  openType);
/*************************************************************************
* @brief     get the connection  operating mode.
* @name      nvsIf_get_connection_var 
* @param     void
*
* @return
*    - 0: USB mode
*    - 1: Wifi mode
***************************************************************************/
extern void nvsIf_get_connection_var(uint8_t *nvs_connection_var);
/*************************************************************************
* @brief     get the simulation bus operating mode.
* @name      nvsIf_get_can_lin_var 
* @param     void
*
* @return
*    - 0: CAN bus mode
*    - 1: LIN bus mode
***************************************************************************/
extern void nvsIf_get_can_lin_var(uint8_t *nvs_can_lin_var);
/*************************************************************************
* @brief     load new simulation config json file from  sdcard and restart 
* @name      nvsIf_loadConfig 
* @param     jsonConfigPath : pointer to the json file path
*
* @return    void
***************************************************************************/
extern void nvsIf_loadConfig(const char *jsonConfigPath);
/*************************************************************************
* @brief     set the caniotBox operating mode.
* @name      caniotBox_set_mode 
* @param     caniotBoxMode : 0 simulation mode
*                            1 simulation mode standalone
*                            2 listenonly mode
*                            3 listenonly standalone
* @return
*    -  0: ESP_OK
*    - -1: ESP_FAIL
***************************************************************************/
extern esp_err_t caniotBox_set_mode(uint8_t caniotBoxMode);
/*************************************************************************
* @brief     send data to caniot application.
* @name      send_caniot_data 
* @param     caniot_message_t : structur content the frame information
*
* @return
***************************************************************************/
extern void send_caniot_data(caniot_message_t *message_arg);
#ifdef __cplusplus
}
#endif
