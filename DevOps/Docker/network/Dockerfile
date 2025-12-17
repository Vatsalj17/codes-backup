FROM python

WORKDIR /myapp

# COPY ./api.py .
# RUN pip install requests
# CMD [ "python", "api.py" ]

COPY ./mongo-cont.py .
RUN pip install pymongo
CMD [ "python", "mongo-cont.py" ]
