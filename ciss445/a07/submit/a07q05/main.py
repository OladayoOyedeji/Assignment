import urllib.request
import re

city_id = 4575352
#api_key = "87ea96ef8f9c158926da485415ef88f6"

api_key = "98b2df1063d25d8c8aa2877058c375b4"
url = "http://api.openweathermap.org/data/2.5/weather?id=%s&mode=xml&units=imperial&APPID=%s"
url = url % (city_id, api_key)
print(url)
xml = urllib.request.urlopen(url).read()
xml = xml.decode("utf-8")
print(xml)

p = re.compile("<city[^>]*>")
search = p.search(xml)
print(search)
city_info = xml[search.span()[0]:search.span()[1]]
p = re.compile("name=.*")
search = p.search(city_info)
print(search)
city_info = city_info[search.span()[0]:search.span()[1]]
print(city_info)
p = re.compile("\".*\"")
search = p.search(city_info)
print(search)
city = city_info[search.span()[0]+1:search.span()[1]-1]
print(city)
# city = 

p = re.compile("<country>.*</country>")
search = p.search(xml)
country_info = xml[search.span()[0]:search.span()[1]]
print(country_info)
p = re.compile(">.*<")
search = p.search(country_info)
country = country_info[search.span()[0]+1:search.span()[1]-1]
print(country)
# country =

p = re.compile("<sun[^>]*>")
search = p.search(xml)
print(search)
sun_info = xml[search.span()[0]:search.span()[1]]
print(sun_info)
p = re.compile("rise=\"[^\"]*\"")
search = p.search(sun_info)
print(search)
sun_rise_info = sun_info[search.span()[0]:search.span()[1]]
print(sun_rise_info)
p = re.compile("set=\"[^\"]*\"")
search = p.search(sun_info)
print(search)
sun_set_info = sun_info[search.span()[0]:search.span()[1]]
print(sun_set_info)
p = re.compile("\".*\"")
search = p.search(sun_rise_info)
sun_rise = sun_rise_info[search.span()[0]+1:search.span()[1]-1]
print(sun_rise)
p = re.compile("\".*\"")
search = p.search(sun_set_info)
sun_set = sun_set_info[search.span()[0]+1:search.span()[1]-1]
print(sun_set)
# sun_rise = ""

# print("City:", city)
# print("Country:", country)
# print("Sun rise:", sun_rise)
