import os
import urllib.parse
import base64
import requests
import pickle
from urllib.parse import urlencode


def encode_to_base64(code):
    encoded_str = urllib.parse.quote(code, safe='')
    base64_str = base64.b64encode(encoded_str.encode()).decode()
    return base64_str


class Client:

    def __init__(self):
        self.cookies = {}
        self.username = None
        self.password = None

        self.cookie_file = 'cookie.txt'
        self.user_agent = "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Safari/537.36"

    def login(self, username, password):
        url = 'https://vjudge.net/user/login'
        headers = {
            "Content-Type": "application/x-www-form-urlencoded",
            "User-Agent": self.user_agent,
        }
        data = {
            'username': username,
            'password': password,
        }
        response = requests.post(url, data=data, headers=headers)
        result = response.text
        print('status code:', response.status_code, 'with result:', result)
        self.cookies = response.cookies
        with open(self.cookie_file, 'wb') as f:
            pickle.dump(response.cookies, f)
        if result != 'success':
            return False
        self.username = username
        self.password = password
        return True

    def fetch(self, oj, problem):
        url = f'https://vjudge.net/problem/{oj}-{problem}'
        headers = {
            "User-Agent": self.user_agent,
        }
        response = requests.get(url, headers=headers, cookies=self.cookies)
        return response

    def load(self, autologin=True):
        self.cookies = requests.cookies.RequestsCookieJar()
        if not os.path.exists(self.cookie_file):
            if autologin:
                username = input('username:')
                password = input('password:')
                return self.login(username, password)
            else:
                return False
        with open(self.cookie_file, 'rb') as f:
            self.cookies.update(pickle.load(f))
        return True

    def submit(self, oj, problem, code, language):
        url = "https://vjudge.net/problem/submit"
        headers = {
            "Content-Type": "application/x-www-form-urlencoded",
            "Referer": f"https://vjudge.net/problem/{oj}-{problem}",
            "User-Agent": self.user_agent,
            "X-Requested-With": "XMLHttpRequest",
        }
        data = {
            'method': 0,
            'language': language,
            'open': 0,
            'source': encode_to_base64(code),
            'captcha': '',
            'oj': oj,
            'probNum': problem,
        }
        # print('data:', data)
        response = requests.post(url, headers=headers, cookies=self.cookies, data=data)
        print('status code:', response.status_code)
        print(response.text)
        return response


if __name__ == '__main__':
    print('Test:')
    client = Client()
    if not client.load():
        username = input('username:')
        password = input('password:')
        client.login(username, password)
    client.submit('BZOJ', '1000', '#include<bits/stdc++.h>\nint main(){int a,b;std::cin>>a>>b;std::cout<<a+b;}', 'cc.std17O2')