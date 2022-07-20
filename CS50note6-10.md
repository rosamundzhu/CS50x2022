<style>
pre {
  overflow-y: auto;
  max-height: 300px;
}
</style>

## Week 6  
python中两种引入lib的方式：
```py
import cs50
x = cs50.get_int("x: ")
```
```py
from cs50 import get_int
x = get_int("x: ")
```
```py
try:   
    x = int(input("x: ")) #转换成int
except:
    print("not an int")
    exit()
try:  
    y = int(input("y: "))
except:
    print("not an int")  
    exit()
print(x+y)
```
```py
for i in range(3):
    for j in range(3):
        print("#", end="")
    print()
print()
for i in range(3):
    print("#" * 3)
```
```py
from sys import argv
if len(argv) == 2:
    print(f"hello, {argv[1]}")
else:
    print("hello world")

# python不包含在argv list中

# python hello.py abc 
# hello, abc
```
```py
import csv
from cs50 import get_string
# pip install --upgrade pip
# pip3 install cs50

name = get_string("Name: ")
number = get_string("Phone: ")

with open("phonebook.csv", "a") as file:
    writer = csv.writer(file)
    writer.writerow([name, number])
```
```py
import csv

houses = {
    "Gryffindor": 0,
    "Hufflepuff": 0,
    "Ravenclaw": 0,
    "Slytherin": 0
}

with open("hogwarts.csv", "r") as file:
    reader = csv.Dicreader(file)
    for row in file:
        house = row["House"]
        houses[house] += 1

for house in houses:
    number = houses[house]
    print(f"{houses},{number}")
```

Objects:
```py
class Student():
    def __init__(self, name, id): #必须有self
        self.name = name
        self.id = id
    def changeID(self, id):
        self.id = id
    def print(self):
        print("{} - {}".format(self.name, self.id))
jane = Student("Jane", 10)
jane.print()
jane.changeID(11)
jane.print()
```

`#!/usr/bin/env python3`  
`chmod a+x <file>`

------
## Week 7  

```py
import csv

titles = {}

# counter = 0

with open("/Users/zhuzixuan/Desktop/computer science/CS50/week7/src7/favorites/favorites.csv", 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row["title"].strip().upper()
        if not title in titles:
            titles[title] = 0
        titles[title] += 1
        # if "OFFICE" in title:
        #     counter += 1

# key = lambda title: titles[title] 
# 相当于
# def get_value(title):
#     return titles[title]

# 只在这里使用一次，没必要def一个new function
for title in sorted(titles, key = lambda title: titles[title], reverse = True):
    print(title, titles[title])
```
`.` any character  
`.*` 0 or more characters  
`.+` 1 or more characters  
`?` optional  
`^` start of input  
`$` end of input  

```py
import csv
import re 

counter = 0

with open("/Users/zhuzixuan/Desktop/computer science/CS50/week7/src7/favorites/favorites.csv", 'r') as file:
    reader = csv.DictReader(file)
    for row in reader: 
        title = row["title"].strip().upper()
        if re.search(".*(OFFICE)$", title):
            counter += 1

print(f"Number of people who like The Office: {counter}")
```


**sqlite**  
`sqlite3 favorites.db`  
`.mode csv`  
`.import favorites.csv favorites`   
退出: `ctrl + D`  
`sqlite3 favorites.db`    
`.schema` 描述database  
`SELECT title FROM favorites;`  
`SELECT DISTINCT(UPPER(title)) FROM favorites;`  
`SELECT COUNT(title) FROM favorites;`  
`SELECT title FROM favorites WHERE title LIKE "office";` 注：这里`LIKE`下的`office`不关注大小写  
`SELECT title FROM favorites WHERE title = "office";` 注：这里`WHERE`下的`office`关注大小写  
`SELECT COUNT(title) FROM favorites WHERE title LIKE "%office%";` 包含所有title中含有office的   
`UPDATE favorites SET title = "The Office" WHERE title = "Thevoffice";`  
`SELECT title, genres FROM favorites WHERE genres = "Comedy";`  

`SELECT DISTINCT(title) FROM shows WHERE id IN (SELECT show_id FROM genres WHERE genre = "Comedy");`   
`INSERT INTO shows (title) VALUES("Seinfeld");`  
`SELECT * FROM shows WHERE title = "Seinfeld";`  
`INSERT INTO genres (show_id, genre) VALUE(159, "Comedy") ORDER BY title;`  

**Interact with Python**
```py
import csv

from cs50 import SQL

db = SQL("sqlite:///favorites.db")

title = input("Title: ").strip()

# 'title' to plug into the question mark
# `db.execute` return a list
# `LIKE` is case-insensitive
rows = db.execute("SELECT COUNT(*) AS counter FROM favorites WHERE title LIKE ?", title)

row = rows[0]

# a dictionary gives the key "counter" and the value corrosponds to
print(row["counter"])
```

**IMDb**  
IMDb, or the Internet Movie Database, has datasets available for download as TSV (tab-separated values) files.

SQL has its own data types:
- **BLOB**, for “binary large object”, raw binary data that might represent files
- **INTEGER**
- **NUMERIC**, number-like but not quite a number, like a date or time
- **REAL**, for floating-point values
- **TEXT**, like strings

`sqlite3 "/Users/zhuzixuan/Desktop/computer science/CS50/week7/src7/imdb/shows.db"`  
`.schema`  
`.table`  
`.time on`  
`SELECT * FROM shows WHERE title = "The Office";`  

model: `CREATE INDEX name ON table (column, ...);` 使用index后，create a data structure of B-trees, 检索速度极大提升  
`CREATE INDEX "title_index" ON "shows" ("title");`  
`SELECT * FROM shows WHERE title = "The Office";`  


`cat filename.sql | sqlite3 movies.db` to check the queries  
in SQL, comments are any lines that begin with `--`

------
## Week 8  
### The Internet
* **Protocols** are a set of rules or conventions, like a physical handshake for humans, that the world has agreed upon for computers to communicate with.  
* **TCP/IP** are two protocols for sending data between two computers.   
  sender: \<data\>; 25/1 of 4; receiver IP -> routing via IP -> to receiver
* **IP** stands for *internet protocol*, a protocol that includes a standard way for computers to address each other. (互联网协议)  
  * *connectless protocol*, not necessarily a defined path from the sender to the receiver
* **IP addresses** are unique addresses for computers connected to the internet, such that a packet sent from one computer to another will be passed along routers until it reaches its destination.  
  * An IP address might have the format `#.#.#.#`, where each number can have a value from 0 to 255. Each number will be the size of one byte, so the entire address will be 4 bytes, or 32 bits. (roughly 4 billion) (IPv4)  
  * a new scheme IPv6 `#.#.#.#.#.#` in the range `[0,ffff]` (eg: `2001:4860::8844`, omit `0`)
* **TCP**, *transmission control protocol*, is a protocol for sending and receiving data. TCP allows for a single server, at the same IP  address, to provide multiple services through the use of a port number, a small integer added to the IP address. (传输控制协议)  
  * to a specific machine or program through a *port number* coupled with an IP address
  * another thing that TCP is crucial for is *guaranteeing delivery* of packets, which IP alone dones not do. TCP also allows for a large amount of data, like an image, to be sent in smaller chunks. 
    * FTP(file transfer) using port: 21
    * SMTP(email) using port: 25
    * DNS using port: 53
    * HTTP using port: 80
    * HTTPs using port: 443
* **DHCP**, *Dynamic Host Configuration Protocol* server, whose role is to assign IP addresses to devices.  
* **Routers** are specialized computers, with CPUs and memory, that routes, or relays, data from one point to another. (路由器)  
A router might have multiple options for what direction to send some data, and there are algorithms that try to figure out that direction.  
one step closer to where supposed to go  
* **UDP**, *User Datagram Protocol*, is another protocol for sending data that does not guarantee delivery like TCP, which might be useful for streaming real-time videos or calls, since we don’t want to wait for all the packets to be redelivered before we get new ones. (用户数据报协议)
* **DNS**, *domain name system*, is another technology that translates domain names like `cs50.harvard.edu` (host) to IP addresses. DNS is generally provided by a server nearby, with a big table in its memory, of domain names and IP addresses. (域名系统)
  * large DNS server systems are more liek aggregators, collecting smaller sets of DNS information and pooling them together, updating frequently.
* **access points**, modern home networks consist of access points that combine a router, a modem, a switch, and other technologies together into a single device.
* **Internet Primer**
### The web
* **HTTP**, or *Hypertext Transfer Protocol*, one such example of an *application layer protocol*, standardizes the format by which the web browsers and web servers communicate within TCP/IP packets.(超文本传输协议)
  * an *HTTP reuqiest line*, `method request-target http-version`, e.g.`GET request-target HTTP/1.1`  
  * **HTTPS** is the secure version of HTTP, ensuring that the contents of packets between the browser and server are encrypted.
* A **URL**, (Uniform Resource Locator) or web address, might look like `https://www.example.com/`.
    * `https://` is the protocol being used.
    * The `/` at the end is a request for the default file. It might also end in something like `/file.html` for a specific file.
    * `example.com` is the domain name. `.com` is a top-level domain name, and others like `.edu` or `.io` indicate what type of website might be hosted there.  
    Today, there are hundreds of top-level domain names, some with restrictions on how they can be used.
    * `www` is the hostname, or subdomain, that refers to one or more specific servers in the domain name. A domain name might include web servers for `www`, or email servers for `mail`, so each subdomain can point to them separately.
    * Together, `www.example.com` is a **fully qualified domain name**, or one that has a specific set of addresses.
  * Two commands supported by HTTP include **GET** and **POST**.  
  **GET** allows a browser to ask for a page or file in a URL, and **POST** allows a browser to send additional data to the server that is hidden from the URL.  
  Both of these are requests we can make to a server, which will provide a response in return.  
* A `GET` request will start with:
    ```
    GET / HTTP/1.1
    Host: www.example.com
    ...
    ```
  * The `GET` indicates that the request is for some file, and `/` indicates the default file. 
  * There are different versions of the HTTP protocol, so `HTTP/1.1` indicates that the browser is using version 1.1.  
  * `Host: www.example.com` indicates that the request is for `www.example.com`, since the same web server might be hosting multiple websites and domains.
* A response for a successful request will start with:
    ```
    HTTP/1.1 200 OK
    Content-Type: text/html
    ...
    ```
  * The web server will respond with the version of HTTP, followed by a status code, which is 200 OK here, indicating that the request was valid.
* The keys and values, like `Host: www.example.com` and `Content-Type: text/html`, are known as **HTTP headers**.<br><br>

In VS Code’s terminal, we can use a command-line tool, `curl`, to see the response headers for a request as well: ``$ curl -I -X GET http://harvard.edu/``  

* **HTTP status codes** include:  
Success: `200 OK`  
Redirection:   
`301 Moved Permanently`   
`307 Temporary Redirect`  
`302 Found` temporaily   
Clinet Error:  
`401 Unauthorized` (requires login credentials)  
`403 Forbidden`(server will not allow this request)  
`404 Not Found`  
Others:  
`304 Not Modified`    
`418 I'm a Teapot`  (An April Fool’s joke years ago)  
Server Error:  
`500 Internal Server Error` generic server failure (Buggy code on a server might result in this status code, like segfaults we might have seen in C. )  
`503 Service Unavailable`  
…
### HTML  
HTML(*Hypertext Markup Language*). It is a lanuguage, but not a programming language.  

common HTML tags: 
* `<b>, </b>` to be boldface  
* `<i>, </i>` to be in italics
* `<u>, </u>` to be underlined
* `<p>, </p>` rendered as a paragraph with space above and below  
* `<hX>, </hX>`  X = [1, 6]  
```html
<!DOCTYPE html>

<html lang="en">
        <head> <!--head cannot be seen, it's in tag-->
            <title>hello, title</title>
        </head>
        <body>
            hello, body here
        </body>
</html>
```
`command + R`刷新网页  
`<ol start=6>, </ol>` ordered list (start at 6)  
`<ul>, </ul>` unordered list  
`<li>, </li>` for array  
`<table>` `<thead>` `<tbody>` a table  
`<tr>` table row  
`<th>Number</th>` the content of table header  
`<td>ABC</td>` table data   
`<form>, </form>` demarcate the beginning and end of an HTML form  
`<div>, </div>` demarcate the beginning and end of an arbitrary HTML page diversion  
`<input name=X type=Y />` X is a unique identifier for that field, Y is what type of data it accepts (self-closing tag); type = text, password, radio, checkbox, submit ...  
`<a href=X>, </a>` a hyperlink to web page X  
`<img src=X ... />` an image located X  
`<!DOCTYPE html>` specific to HTML5, ltes the browser know what's the standard you're using  
```html
<!--在图片展示出来前先展示文字"Harvard University"-->
<img alt="Harvard University" src="harvard.jpg">
```
```html
<!--自动播放，循环，静音-->
<video autoplay loop muted width="1280">
    <source src="halloween.mp4" type="vidoe/mp4">
</video>
<iframe allowfullscreen src="https://www.youtube.com/watch?v=xvFZjo5PgG0"></iframe>
```
```html
<body>
    <!--hyperlink-->
    visit <a href="https://www.harward.edu/">harvard.edu</a>
</body>
```
```html
<head>
    <!--注意是添加在head中-->
    <!--width调整为device-width-->
    <meta name="viewpoint" content="initial-scale=1, width=device-width">
</head>
```
`https://wwww.example.com/path?key=value`. Here, the `?` indicates that we’re adding inputs, which will include one or more key-value pairs.

```html
<!--把输入的data传送到action后的网址中-->
<form action="https://www.google.com/search" method="get">
    <!--取消自动填充；光标在输入栏中；Query是灰色的-->
    <input atuocomplete="off" atuofocus name="q" placeholder="Query" type="text">
    <input type="submit">
</form>
<!--输入cats后，the website will be"https://www.google.com.hk/search?q=cats"-->
```
`<div>`  
`<header>` `<main>` `<footer>`  
```html
<!--把相同的属性附在body中-->
<body style="text-align: center;">
    <header style="font-size: large;">
        John Harvard
    </header>
    <main style="font-size: medium;">
        welcome to this page
    </main>
    <footer style="font-size: small;">
        this is footer &#169; John Harvard
        <!--HTML entity-->
    </footer>
</body>
```
或者利用**CSS**直接在header中定义style:
```html
<head>
    <title>paragraphs</title>
    <!--body共同的特性放在这里-->
    <!--Cascading Style Sheets-->
    
    <style>
        body
        {
            text-align: center;
        }
        
        header
        {
            font-size: larger;
        }
        
        main 
        {
            font-size: medium;
        }
        
        footer
        {
            font-size: small;
        }
    </style>
</head>
```
### CSS 
CSS(*Cascading Style Sheets*)  
identifying a *selector* (e.g. body); key-value  
using `<style>` in head or create a css file and then `<link href="xxx.css" rel="style">`  
* common CSS properties:
  - border: style color width
  - background-color: [keyword | #<6-digit hex>]
  - color: [keyword | #<6-digit hex>] (keywords; fixed points; percentage; base off the most recent(larger))
  - font-size: [absolute size | relative size]
  - font-family: [font name | generic name]
  - text-align: [left | right | center]
* tag selector
```css
h2
{
    font-family: times;
    color: #fefefe;
}
table
{
    border: 5px solid, red;
}
tr
{
    height: 50px;
}
td
{
    background-color: black;
    color: white;
    font-size: 22pt;
    font-family: georgia;
    text-align: center;
    width: 50px;
}
```
* ID selector (obly to a unqiue identifier)
```css
#unique
{
    border: 4px dotted blue;
    text-align: right;
}
```
* class selector
```css
    .students
    {
        backgroud-color: yellow;
    }
```
```css
body
{
    background-color: blue;
}
```
inventing a new class:
```html
<!DOCTYPE html>

<html lang="en">               
        <head>
            <link href="test.css" rel="stylesheet">
            <title>paragraphs</title>
        </head>
        <body class="center">
            <header class="large">
                John Harvard
            </header class="medium">
            <main>
                welcome to this page
            </main>
            <footer  class="small">
                this is footer &#169; John Harvard
            </footer>
        </body>
</html>
```
set a `.css` file
```css
.center
{
    text-align: center;
}

.large
{
    font-size: large;
}

.medium
{
    font-size: medium;
}

.small
{
    font-size: small;
}
```
`<p id = "first"></p>` 给予一个id，再用`#first`设置属性。
### Javascript
Javascript is a modern programming language (a *object-oriented* programming language) 
With JavaScript, we can change the HTML in the browser in real-time. We can use `<script>` tags to include our code directly, or from a `.js` file. (or `<style>` or `<link>`)  
```
nums = nums.map(function(num){
    return num * 2
});
```
*event* in HTML and JavaScript is a response to user interaction with the web page  
JavaScipt has support for *event handlers*, which are call-back functions that respond to HTML events  
```html
<button onclick = "alertName(event)">Button 1</button>
```
```js
function alertName(event)
{
    var trigger = event.srcElement;
    alert('You clicked on ' + trigger.innerHTML);
}
```
### DOM 
**DOM**, *document object model*
DOM properties:
- innerHTML: holds the HTML inside a set of HTML tags
- nodeName: the name of an HTML element of element's attribute
- id: the "id" attribute of an HTML element
- parentNode: a reference to the node one level up in the DOM
- childNodes: an array of references to the nodes one level down in the DOM
- attributes: an array of attributes of an HTML element
- sytle: an object encapsulating the CSS/HTML styling of an element
DOM methods:  
- getElementByid(id): Gets the elements with a given ID below this point in the DOM
- getElementByTagName(tag): gets all elements with the given tag below this point in the DOM
- appendChild(node): add the given node to the DOM below this point
- removeChild(node): remove the specified child node from the DOM  

**jQuery**: a popular open-source liabrary  
`$('#colorDiv').css('background-color', 'green')`


For example:
1. individual function: `<button onclick="turnPurple();">Purple</button>`  
2. general purpose function: `<button onclick= "changeColor('purple');">Purple</button>`
```js
function changeColor(color)
{
    document.getElementById('colorDiv').style.backgroundColor = color;
}    
```
3. Event handler: `<button onclick= "ChangeColorEvent(event);">Purple</button>`
```js
// button上的word小写后放进来
function ChangeColorEvent(event)
{
    var triggerObject = event.srcElement;
    document.getElementById('colorDiv').style.backgroundColor = triggerObject.innerHTML.toLowerCase()
}
```
4. Using jQuery: (https://api.jquery.com)  `<button class="jQButton">Purple</button>`
```js
$(document).ready(function(){ //fully loaded
    $('.jQButton').click(function(){ //any jQButton is clicked, give an attribute
        $('#colorDiv').css('background-color', this.innerHTML.toLowerCase());
    });
});
```
## Week 9
### FLASK  
`app = Flask(__name__)` is to initiate a Flask application  
`app.route("/")` as **decorators**, in Flask to associate a particular function with a particular URL.  
`flask run` to run the Flask application  
`url_for()` to associate with the decorator  
`redirect()` to redirect you from ont page to another  
`session()` to track that a user is logged in. a sort of like a global variable  
`render_template()` is used to create pages on your site that mix HTML and python together  

to pass data in our application, can use:  
```py
# to collect infromtion using HTTP get
@app.route("/show/<number>")
def show(number):
    return "you passed in {}".format(number)
```
```py
# to pass in data via HTML forms by HTTP POST 
@app.route("/login", methods=['GET', 'POST'])
def login():
    # go and retrieve from the from the field called username
    if not request.form.get("username")
        return apology("must provide username")
```

**Version 1**:  
```py
# app.py
from flask import Flask, render_template, request

app = Flask(__name__)

#if I go to my web applications home page
@app.route("/")
def index():
    name = request.args.get("name")
    return render_template("index.html", name=name)
```
```html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>
    <body>
        <!--put the name of variable that you want to plug in-->
        hello, {{ name }} 
    </body>
</html>
```
`flask run`  
`http://127.0.0.1:5000/?name=Rosamund` to get a request, key-value pair   

**Version 2**:
```py
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

# the behavior I want to appear on different pages within my flask applicaiotn
@app.route("/greet")
def greet():
    name = request.args.get("name")
    return render_template("greet.html", name=name)
```
```html
<!--index.html-->
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>
    <body>
        <!--put the name of variable that you want to plug in-->
        <form action="/greet" method="get">
            <input autocomplete="off" autofocus name="name" placeholder="Name" required type="text">
            <input type="submit">
        </form>
    </body>
</html>
```
```html
<!--greet.html-->
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>greet</title>
    </head>
    <body>
        hello, {{ name }}
    </body>
</html>
```
the url will be `http://127.0.0.1:5000/greet?name=david`

a new version to avoid redundancy is to  
set a new html
```html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>
```
then change the index.html to 
```jinja
{% extends "layout.html" %}

{% block body %}

    <form action="/greet" method="get">
        <input autocomplete="off" autofocus name="name" placeholder="Name" required type="text">
        <input type="submit">
    </form>

{% endblock %}
```
change the greet.html to 
```jinja
{% extends "layout.html" %}

{% block body %}

    hello, {{ name }}

{% endblock %}
```

to show nothing in the url
```py
@app.route("/greet", methods=["Post"])
def greet():
    # request.args is for "GET"
    # request.form is for "POST"
    name = request.form.get("name", "world")
    return render_template("greet.html", name=name) #传递name
```
```html
    <!--change to post-->
    <form action="/greet" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" required type="text">
        <input type="submit">
    </form>
```

-  another version
```py
from flask import Flask, render_template, request

app = Flask(__name__)

# a global variable
SPORTS = [
    "Basketball",
    "Soccer", 
    "Ultimate Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register(): #could be greet() but to be consistent
    # validate submission
    if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        return render_template("failure.html")

    #confirm registration
    return render_template("success.html")
```
- selected box:
```html
{% extends "layout.html" %}
{% block body %}

    <h1>Register</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="sport">
            <option disable selected>Sports</option>
            {% for sport in sports %}
                <option>{{ sport }}</option>
            {% endfor %}
        </select>
        <input type="submit" value="Register">
    </form>

{% endblock %}
```
- checkbox
```html
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        {% for sport in sports %}
            <!--如果是type="radio"那么mutually exclusive,只能选择一个-->
            <input name="sport" type="checkbox" value="{{ sport }}"> {{ sport }}
        {% endfor %}
        <input type="submit" value="Register">
    </form>
```
### AJAX
Ajax, formerly *Asynchronous JavaScipt and XML*) allows to dynamically update a webpage more dynamically (no need to reload the page) by using XMLHttpRequest (`var xtthp = new XMLHttpRequest();`)  
Once you have the object, the first thing you have to do is define an onreadystatechange behavior. An **anonymous funcion** will be called when the asynchronous HTTP request has completed and thus typically defines what is expected to change on your site.  
readyState range from 0 to 4.
```js
function ajax_request(argument)
{
    var aj = new HMLHttpRequest();
    // the fuction is to execute on the readyState changing
    aj.onreadystatechange = function() {
        //but only going to have a meaningful thing to do once the readyState is 4 
        if (aj.readyState == 4 && aj.status == 200 )
            // do sth to the page
    }

    aj.open("GET", /* url */, true);
    aj.send()
}
```

Accessing Form Data:  
HTML
```html
<input name="password" ... />
```
Python 
```py
request.form.get("password")
```

Passing Values Into Templates:
```py
return render_template("hello.html", name="Brian")
```
Jinja Templates
```html
<p>hello, {{ name }}</p>
```

Looping in Template  
Python
```py
return render_template("hello.html",
    contacts=[{"name":"Brian", "house":"Winthrop"},
              {"name":"David", "house":"Mather"}])
```
Jinja Template
```html
{% for contact in contacts %}
    <p>{{ contact.name }} lives in {{ contact.house }}</p>
{% endfor %}
```

## Week 10  
the memory of the elements in an array are stored **contiguously**   
'in random locations that happen to be available' is probably describing your use of malloc in the heap  
