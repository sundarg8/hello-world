import json;

def search_json_name(value, json_data):
    for row in json_data:
        if row["name"] == value:
            return row;

def v4_post_handler_app(environ, start_response):
    
    try:
        request_body_size = int(environ.get('CONTENT_LENGTH', 0))
    except (ValueError):
        request_body_size = 0

    request_body = environ['wsgi.input'].read(request_body_size)
    req_data = json.loads(request_body)
    share_name = req_data['name']

    with open('f2data.json', 'r') as f:
        disk_json_data = json.load(f)

    str_ret_data = search_json_name(share_name, disk_json_data)
    json_ret_data = json.dumps(str_ret_data)

    start_response('200 OK', [('Content-Type', 'application/json')])
    yield json_ret_data.encode('utf-8')
    

  
def v3_application(environ, start_response):
  data = {
    'name'   : 'CSCO',
    'shares' : 112,
    'price'  : 32.54
  }

  with open('f2data.json', 'r') as f:
      data2 = json.load(f)

  start_response('200 OK', [('Content-Type', 'application/json')])
  json_str = json.dumps(data2)
  yield json_str.encode('utf-8')



def v2_application(environ, start_response):
  data = {
    'name'   : 'CSCO',
    'shares' : 112,
    'price'  : 32.54
  }

  #with open('data.json', 'w') as f:
  #    json.dump(data, f);

  #data2 = {}
  with open('data.json', 'r') as f:
      data2 = json.load(f)

  start_response('200 OK', [('Application', 'json')])

  json_str = json.dumps(data2)
  yield json_str.encode('utf-8')
