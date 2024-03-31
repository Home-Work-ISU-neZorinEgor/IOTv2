import time

import paho.mqtt.client as mqtt

broker_address = "broker.emqx.io"
broker_port = 1883
topic = "lab/ESP8266_AC2A/strip/set_leds"


def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker with result code " + str(rc))


def send_empty_message():   # лента кривая, ставит цвета только при повторном нажатии
    client.publish(topic, payload="")


def set_led_color(color, num_leds):
    payload = color * num_leds
    client.publish(topic, payload=payload)


client = mqtt.Client()
client.on_connect = on_connect
client.connect(broker_address, broker_port)
client.loop_start()

time.sleep(1)   # что бы сначала увидеть статус подключения
while True:
    send_empty_message()
    input_color = input("Введите цвет в формате RGB (например, 255000000 для красного): ")
    input_num_leds = int(input("Введите количество светодиодов: "))
    set_led_color(input_color, input_num_leds)
    print(f"Сообщение с цветом {input_color} для {input_color} светодиодов отправлено на тему {topic}")

client.loop_stop()
client.disconnect()
