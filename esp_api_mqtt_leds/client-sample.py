import time
import paho.mqtt.client as mqtt

broker_address = "broker.emqx.io"
broker_port = 1883

topic_set_leds = "lab/ESP8266_AC2A/strip/set_leds"
topic_rotate_leds = "lab/ESP8266_AC2A/strip/rotate_leds"
topic_range = "lab/ESP8266_AC2A/range"


def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker with result code " + str(rc))


def send_empty_message():   # лента кривая, ставит цвета только при повторной отправке сообщения
    client.publish(topic_set_leds, payload="")


def set_led_color(color, num_leds):
    payload = color * num_leds
    client.publish(topic_set_leds, payload=payload)


def set_leds():
    send_empty_message()
    input_color = input("Введите цвет в формате RGB (например, 255000000 для красного): ")
    input_num_leds = int(input("Введите количество светодиодов: "))
    set_led_color(input_color, input_num_leds)
    print(f"Сообщение с цветом {input_color} для {input_num_leds} светодиодов отправлено на тему {topic_set_leds}")
    print("---------------- set leds colors ----------------")


def rotate_leds():
    client.publish(topic_rotate_leds, payload="next")
    print("---------------- rotate leds ----------------")


def set_range():
    start_index = int(input("Введите начальный индекс: "))
    end_index = int(input("Введите конечный индекс: "))
    color = input("Введите цвет в формате RGB (например, 255000000 для красного): ")
    payload = f"{start_index},{end_index},{color}"
    client.publish(topic_range, payload=payload)
    print(f"Диапазон от {start_index} до {end_index} установлен с цветом {color}")
    print("---------------- set range ----------------")


client = mqtt.Client()
client.on_connect = on_connect
client.connect(broker_address, broker_port)
client.loop_start()

time.sleep(1)   # что бы сначала увидеть статус подключения

while True:
    input_mode = int(input("Select work-mod: \n1. set_leds\n2. rotate_leds\n3. range\n4. exit"))
    if input_mode == 1:
        set_leds()
    elif input_mode == 2:
        rotate_leds()
    elif input_mode == 3:
        set_range()
    elif input_mode == 4:
        break

client.loop_stop()
client.disconnect()
