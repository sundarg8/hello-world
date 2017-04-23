import json;
import sqlite3


def search(name, search_data):
    for p in search_data: 
        if p["name"] == name: 
            return p 

def create_project(conn, project): 
    sql = '''INSERT INTO  stocks(name, shares, price) 
             VALUES(?,?,?)''' 
    cur = conn.cursor()
    cur.execute(sql, project)
    return cur.lastrowid


if __name__ == '__main__':

    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()

    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks
                 (name text, shares real, price real)''')

    json_string = '[ \
                    { "name" : "CSCO", "shares" : 50, "price"  : 25 }, \
                    { "name" : "NEXT", "shares" : 100, "price"  : 35 } \
                   ] ' 

    with open('l2data.json', 'r') as f:
        disk_json_data = json.load(f)

    #parsed_json = json.loads(json_string);
    #print(parsed_json['name']);

    str_data = search("NEXT", disk_json_data)
    #print (str_data);   

    json_upl_data = json.dumps(str_data)
    #print (str_data["name"])
    #print (str_data["shares"])
    #print (str_data["price"])

    f1 = str_data["name"]
    f2 = str_data["shares"]
    f3 = str_data["price"]

    #print (type(f1))
    #print (type(f2))

    #print (disk_json_data);   
    #str_data.append("
 
    #c.execute("INSERT INTO stocks VALUES(f1, f2, f3)")

    #project = (f1, f2, f3)
    project = (str_data["name"], str_data["shares"], str_data["price"])
    project_id = create_project(conn, project);

    conn.commit()
    t = ('NEXT',)
    #cursor.execute('SELECT * FROM stocks WHERE name=?', t)
    #print(cursor.fetchone())
  
    for row in cursor.execute('SELECT * FROM stocks WHERE name=?', t):
        print(row[1])
        json_upl_string={"name": row[0], "shares": row[1], "price": row[2]}
        #print (json_upl_string)
 
    json_ret_data = json.dumps(json_upl_string)     
    print(json_ret_data)
    conn.close()
        

