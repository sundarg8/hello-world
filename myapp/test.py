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

    #project = (str_data["name"], str_data["shares"], str_data["price"])
    #project_id = create_project(conn, project);
    #conn.commit()
    #cursor.execute('SELECT * FROM stocks WHERE name=?', t)
    #print(cursor.fetchone())

    t = ('SHAC',)
  
    for row in cursor.execute('SELECT * FROM stocks WHERE name=?', t):
        json_upl_string={"name": row[0], "shares": row[1], "price": row[2]}
 
    json_ret_data = json.dumps(json_upl_string)     
    print(json_ret_data)
    conn.close()
        

