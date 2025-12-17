FROM python

WORKDIR /myapp

COPY ./youtube_manager_mongodb.py .

RUN pip install pymongo

CMD [ "python", "youtube_manager_mongodb.py" ]
