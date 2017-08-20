/*
* MQTT client for lwIP

* Author: Erik Andersson

* Details of the MQTT protocol can be found at:
http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html 
*
*/

//#include "oneNet_MQTT.h"
#include "mqtt.h"
#include "string.h"

#include "los_sys.h"
#include "los_tick.h"
#include "los_task.ph"
#include "los_config.h"

typedef struct
{
    uint8_t name[32];
    uint64_t uptime;
    //LOS_TickCountGet
    uint32_t priqueue_size;//LOS_PriqueueTotalSize
    uint32_t cycle_pre_tick;//LOS_CyclePerTickGet
    uint32_t current_task; //LOS_CurTaskIDGet
}mqtt_device_t;

static mqtt_device_t mqtt_device = {
    .name = "xiaxiaowen's IOT device",
    .uptime = 0,
    .priqueue_size = 0,
    .cycle_pre_tick = 160000,
    .current_task = 0x00000000UL
};

ip_addr_t mqttServerIpAddr;

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);
void mqtt_pub_request_cb(void *arg, err_t result);
void mqtt_sub_request_cb(void *arg, err_t result);
//1. Initial steps, reserve memory and make connection to server:

//1.1: Provide storage

//Static allocation: //����������ת�Ƶ� MAIN.c ��
//  mqtt_client_t static_client;

//  example_do_connect(&static_client);

//Dynamic allocation:
//  mqtt_client_t *client = mqtt_client_new();
//  if(client != NULL) {
//    example_do_connect(&client);
//  }

//1.2: Establish Connection with server

void example_do_connect(mqtt_client_t *client)
{
    struct mqtt_connect_client_info_t ci;
    
    err_t err;
    
    /* Setup an empty client info structure */
    memset(&ci, 0, sizeof(ci));
    
    /* Minimal amount of information required is client identifier, so set it here */ 
    ci.client_id = "xiaxiaowen_01";
    
    // MQTT��������ַΪ��59.110.142.105�˿ں�Ϊ��1883
    IP4_ADDR(&mqttServerIpAddr, 192, 168, 1, 5);//���� MQTT ��������ַ
    
    /* Initiate client and connect to server, if this fails immediately an error code is returned
    otherwise mqtt_connection_cb will be called with connection result after attempting 
    to establish a connection with the server. 
    For now MQTT version 3.1.1 is always used */
    
    //MQTT �������������� ,��ע�� �����ӽ�������Ļص�������2017��4��12��09:00:12
    
    err = mqtt_client_connect(client, &mqttServerIpAddr, 1883, mqtt_connection_cb, 0, &ci);
    
    /* For now just print the result code if something goes wrong */
    if(err != ERR_OK) 
    {
        printf("mqtt_connect return %d\n", err);
    }
}

//Connection to server can also be probed by calling mqtt_client_is_connected(client) 

//-----------------------------------------------------------------
//2. Implementing the connection status callback
//ִ������״̬ �� �ص�����
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    err_t err;
    if(status == MQTT_CONNECT_ACCEPTED) 
    {
        printf("mqtt_connection_cb: Successfully connected\n");
        
        /* Setup callback for incoming publish requests */
        //ע�� ��Ϣ���� �ص����� �Լ���Ϣ���ݵ����Ĵ�����
        mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);
        
        /* Subscribe to a topic named "subtopic" with QoS level 2, call mqtt_sub_request_cb with result */ 
        err = mqtt_subscribe(client, "time", 1, mqtt_sub_request_cb, arg);
        
        if(err != ERR_OK)
        {
            printf("mqtt_subscribe return: %d\n", err);
        }
    } 
    else 
    {
        printf("mqtt_connection_cb: Disconnected, reason: %d\n", status);
        
        /* Its more nice to be connected, so try to reconnect */
        example_do_connect(client);
    }  
}

void mqtt_sub_request_cb(void *arg, err_t result)
{
    /* Just print the result code here for simplicity, 
    normal behaviour would be to take some action if subscribe fails like 
    notifying user, retry subscribe or disconnect from server */
    printf("Subscribe result: %d\n", result);
}

//-----------------------------------------------------------------
//3. Implementing callbacks for incoming publish and data

/* The idea is to demultiplex topic and create some reference to be used in data callbacks
Example here uses a global variable, better would be to use a member in arg
If RAM and CPU budget allows it, the easiest implementation might be to just take a copy of
the topic string and use it in mqtt_incoming_data_cb
*/

//���������� һ�� ���� ��Ϣͷ һ�� ���� ����� ����

static int inpub_id;
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    
    //��Ϣ����֮���Ƚ������������ж� ��ʲô���� �ģ�2017��4��20��09:25:51
    
    printf("Incoming publish at topic \" %s \" with total length %u\r\n", topic, (unsigned int)tot_len);
    
    /* Decode topic string into a user defined reference */
    if(strcmp(topic, "time") == 0) 
    {
        inpub_id = 0;
    }
    else if(topic[0] == 'A')        
    {
        /* All topics starting with 'A' might be handled at the same way */
        inpub_id = 1;
    }
    else
    {
        /* For all other topics */
        inpub_id = 2;
    }
}

static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    //��Ϣ����֮�����ж����� �����Ǹ�������Ȼ���������Ǹ��ݲ�ͬ�����⣬���в�ͬ�Ĵ���
    
    uint8_t tempBuff[20]={0};
    
    uint8_t i;
    
    //���ݸ��Ƶ���������������  �ַ���0����β����Ϊ ���͹���ֻ�ܷ��� �ַ� ���ܷ����ַ�����2017��4��20��09:24:43
    for(i=0;i<len;i++)
    {
        tempBuff[i]=data[i];
    }
    tempBuff[i]=0;
    
    
    printf("Incoming publish payload with length %d, flags %u\n", len, (unsigned int)flags);
    
    if(flags & MQTT_DATA_FLAG_LAST) 
    {
        /* Last fragment of payload received (or whole part if payload fits receive buffer
        See MQTT_VAR_HEADER_BUFFER_LEN)  */
        
        /* Call function or do action depending on reference, in this case inpub_id */
        if(inpub_id == 0) 
        {
            /* Don't trust the publisher, check zero termination */
            if(tempBuff[len] == 0) 
            {
                printf("mqtt_incoming_data_cb: %s\n", (const char *)data);
            }
        }
        else if(inpub_id == 1) 
        {
            /* Call an 'A' function... */
        }
        else 
        {
            printf("mqtt_incoming_data_cb: Ignoring payload...\n");
        }
    }
    else 
    {
        /* Handle fragmented payload, store in buffer, write to file or whatever */
    }
}

//-----------------------------------------------------------------
//4. Using outgoing publish

//ʹ�� ����������Ϣ
//MQTT�������Ϣ��Ϊ�����⣨Topic���͸��أ�payload��������

void example_publish(mqtt_client_t *client, void *arg)
{
    
    static uint16_t temp = 0;
    //const char *pub_payload= "Hello,MQTT!\r\n";//���͵���Ч����(����)
    err_t err;
    /*
    *    ���һ�Σ���һ����ᷢ����Ϣ��ʧ���ظ�����Ϣ���������ڵײ�TCP/IP���硣����<=1
    *    ����һ�Σ���һ�����ȷ����Ϣ�������Ϣ���ܻ��ظ�������>=1
    *    ֻ��һ�Σ�ȷ����Ϣֻ��һ�ε��������1����һЩҪ��Ƚ��ϸ�ļƷ�ϵͳ�У�����ʹ�ô˼���
    */
    u8_t qos = 1; /* 0 1 or 2, see MQTT specification */
    
    //=0 ����˼Ӧ���ǲ�������Ч���أ���Ч���ݣ�
    u8_t retain = 0; /* No don't retain such crappy payload... */
    //temp = LM75A_ReadTemperature();
    //printf("temp:%d.%d\r\n", temp/100, temp%100);
    
    mqtt_device.uptime          = LOS_TickCountGet();
    mqtt_device.priqueue_size   = LOS_PriqueueTotalSize();
    mqtt_device.cycle_pre_tick  = LOS_CyclePerTickGet();
    mqtt_device.current_task    = LOS_CurTaskIDGet();
    
    err = mqtt_publish(client, "device", &mqtt_device, sizeof(mqtt_device), qos, retain, mqtt_pub_request_cb, arg);
    
    if(err != ERR_OK)
    {
        printf("Publish err: %d.\r\n", err);
    }
    else
    {
        printf("Publish Success.\r\n");
    }
}

/* Called when publish is complete either with sucess or failure */
//������Ϣ��ɺ� �� �ص�����
void mqtt_pub_request_cb(void *arg, err_t result)
{
    if(result != ERR_OK)
    {
        printf("Publish result: %d\n", result);
    }
}

static mqtt_client_t static_client;
static UINT32 g_uwmqttClientTaskID;

LITE_OS_SEC_TEXT VOID mqtt_client_create(VOID)
{
    static_client.conn_state=0;
    /* Initialize MQTT client */
    example_do_connect(&static_client);
    
    while(1)
    {
        example_publish(&static_client,(void *)mqtt_pub_request_cb);
        
        LOS_TaskDelay(2000);
    }
}
void mqtt_client_init(void)
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stTaskInitParam;
    
    (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
    stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)mqtt_client_create;
    stTaskInitParam.uwStackSize = 512;
    stTaskInitParam.pcName = "mqttClient";
    stTaskInitParam.usTaskPrio = 10;
    uwRet = LOS_TaskCreate(&g_uwmqttClientTaskID, &stTaskInitParam);
    
    if (uwRet != LOS_OK)
    {
        return;
    }
    return;
}

//-----------------------------------------------------------------
//5. Disconnecting

//Simply call mqtt_disconnect(client)