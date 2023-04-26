#pragma once

#define SAFE_DELETE(x) if(x) { delete(x); x = 0;}
#define SAFE_DELETE_ARRAY(x) if(x) { delete[](x); x = 0;}