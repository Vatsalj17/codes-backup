FROM node:20

WORKDIR /myapp

COPY . .
# or can be written as COPY . /myapp

RUN npm install

EXPOSE 3000

CMD [ "npm", "start" ]
