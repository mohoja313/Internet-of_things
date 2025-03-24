import telebot
from telebot import types
import requests
import json
url = "http://10.31.65.87/setStatus"
Pay = '123'
payload = {
    "ledStatus":0
}
payload_t = {
    "ledStatus":1
}
headers = {
    "Content-Type": "application/json"
}

bot=telebot.TeleBot("bot token")
@bot.message_handler(commands=['start'])
def send_welcome(message):
    sender_id = message.from_user.id
    sender_name = message.from_user.first_name
    
    print(f"Sender ID: {sender_id}")
    print(f"Sender Name: {sender_name}")
    keyboard = types.ReplyKeyboardMarkup(row_width=1, resize_keyboard=True)
    button2 = types.KeyboardButton('/کنترل_چراغ')
    button1 = types.KeyboardButton('/help')
    keyboard.add(button1, button2)
    bot.send_message(message.chat.id, 'انتخاب کنید', reply_markup=keyboard)
@bot.message_handler(commands=['help'])
def help_me(message):
    bot.reply_to(message, "با زدن دکمه کنترل چراغ و وارد کردن رمز کاربری میتوانید چراغ را کنترل کنید")
@bot.message_handler(commands=['کنترل_چراغ'])
def passw(message):
    bot.reply_to(message,"رمز عبور را وارد کنید")
@bot.message_handler(func=lambda message: message.text == Pay)
def light(message):
    markup = types.InlineKeyboardMarkup()
    button1 = types.InlineKeyboardButton("روشن", callback_data='first')
    button2 = types.InlineKeyboardButton("خاموش", callback_data='second')
    markup.row(button1,button2)
    bot.reply_to(message, 'انتخاب کنید', reply_markup=markup)
@bot.callback_query_handler(func=lambda call:True)
def callback_handler(call):
    if call.data == 'first':
        print("on")
        json_payload_t = json.dumps(payload_t)
        response_t = requests.post(url, data=json_payload_t, headers=headers)
        if response_t.status_code == 200:
            # Request successful
            print("light turn on.")
    elif call.data == 'second':
        print("off")
        json_payload = json.dumps(payload)
        response = requests.post(url, data=json_payload, headers=headers)
        if response.status_code == 200:
            print("light turn off.")


bot.infinity_polling()