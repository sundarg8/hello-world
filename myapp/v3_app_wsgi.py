import json;
import sqlite3;

def search_json_name(value, json_data):
    for row in json_data:
        if row["name"] == value:
            return row;


def connect_to_table(db_str):
    conn = sqlite3.connect(db_str)
    cur = conn.cursor()
    cur.execute('''CREATE TABLE IF NOT EXISTS stocks
                 (name text, shares real, price real)''')
    return conn


def create_project(conn, project):
    sql = '''INSERT INTO  stocks(name, shares, price)
             VALUES(?,?,?)'''
    cur = conn.cursor()
    cur.execute(sql, project)
    return cur.lastrowid

def get_cursor(conn):
    cur = conn.cursor()
    return cur


def v4_post_handler_app(environ, start_response):
    
    try:
        request_body_size = int(environ.get('CONTENT_LENGTH', 0))
    except (ValueError):
        request_body_size = 0

    request_body = environ['wsgi.input'].read(request_body_size)
    req_data = json.loads(request_body)
    share_name = req_data['name']
    cmd = req_data['type']

    conn = connect_to_table('example.db')
    cursor = get_cursor(conn)

    if cmd == 'conf':
        project = (req_data['name'], req_data['shares'], req_data['price'])
        project_id = create_project(conn, project)
        conn.commit()

    match_str = (share_name,)


    for row in cursor.execute('SELECT * FROM stocks WHERE name=?', match_str):
        json_upl_string={"name": row[0], "shares": row[1], "price": row[2]}

    conn.close();


    json_ret_data = json.dumps(json_upl_string)

    start_response('200 OK', [('Content-Type', 'application/json')])
    yield json_ret_data.encode('utf-8')
    

