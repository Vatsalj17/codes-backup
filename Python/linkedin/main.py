from linkedin_scraper import Person, actions
from selenium import webdriver
driver = webdriver.Chrome()

email = "vatsaljaiswal17@gmail.com"
password = "YaTsal@&2587(}{]%"
actions.login(driver, email, password) # if email and password isnt given, it'll prompt in terminal
person = Person("https://www.linkedin.com/in/vatsalj17", driver=driver)
print(person.scrape(close_on_complete=False))
