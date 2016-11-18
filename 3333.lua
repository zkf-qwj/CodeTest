--ngx.header.content_type = "text/plain";
local cjson = require("cjson")
local request_method = ngx.var.request_method


local socket=require("socket");
local host="127.0.0.1"
local port=3000



client:send(from_table_to_json(result))

