from lib import Client
import os
import time

dirname = os.path.dirname(os.path.abspath(__file__))
source_dir = os.path.join(dirname, '../../黑暗爆炸')
target_dir = os.path.join(dirname, '../../BZOJ')

attempted = os.listdir(target_dir)

client = Client()
client.load()

for problem in os.listdir(source_dir):
    if problem in attempted:
        continue
    for submission in os.listdir(os.path.join(source_dir, problem)):
        if 'AC' in submission:
            print(problem, submission)
            client.fetch('BZOJ', problem)
            time.sleep(5)
            code = open(os.path.join(source_dir, problem, submission), 'r', encoding='utf8').read()
            response = client.submit('BZOJ', problem, code, 'cc.std17O2')
            text = response.text
            if 'exist' in text:
                continue
            elif 'runId' in text:
                attempted.append(problem)
                os.mkdir(os.path.join(target_dir, problem))
                time.sleep(60)
                break
            else:
                exit(1)