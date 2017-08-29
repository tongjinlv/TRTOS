/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
**************************************************************************************/
#ifndef _JSON_H_
#define _JSON_H_
#include <Include.h>


typedef enum 
{
	JOT_Obj=0,
	JOT_String=1,
	JOT_Int=2,
	JOT_Float=3,
	JOT_Node=4
}JSON_OBJECT_TYPE;

typedef struct JSON_Node{  
					
		struct JSON_Node *Next;  
		struct JSON_Node *Son;  
		uint8 *Option;
		void *Value;
		uint8 Type;
}JSON_Node;  

JSON_Node *Json_New_Node(void);
uint8 *Json_ToString(JSON_Node *JNCur);


#define JSONTYPE_KV 1  
#define JSONTYPE_ARR 2  
	
/** 
*键值对 
*/  
typedef struct _JSONNode{  
					
		struct _JSONNode *next;  
		struct _JSONNode *prev;  
			
		//JSONOBJ  
	 int type;            //Node类型，分为普通键值对和JSON数组   
	 char *key;           //键  
	 int keyLength;       //键字符串的长度  
			
	 //key_value          type==JSONTYPE_KV  
	 char *value;     //值  
	 int valueLength;     //值字符串长度  
	 //JSONARRAY ARRAY    type==JSONTYPE_ARR  
	 int arrayLength; //值为JSON数组时数组元素个数<span style="font-family: Arial, Helvetica, sans-serif;">             </span>  
	 struct _JSONObjectNode **objectNode; //数组  
}JSONNode;  
	
/** 
* JSONObject 主要用于JSON数组 
*/  
typedef struct _JSONObjectNode{  
		//JSONARRAY  
		JSONNode **jsonNode;      //JSON Obj中的jsonNode链表，也就是每个JSON对象中的所有键值对都有链表存储  
		int length;                //链表的长度  
		struct _JSONObjectNode *next;  //指向下一个jsonNode节点  
}JSONObjectNode;  
	
/** 
* JSON主干列表 
*/  
typedef struct _JSONList{  
				JSONNode *start;    
				JSONNode *end;  
				int length;  
}JSONList;  

#endif
