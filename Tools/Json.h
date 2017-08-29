/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
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
*��ֵ�� 
*/  
typedef struct _JSONNode{  
					
		struct _JSONNode *next;  
		struct _JSONNode *prev;  
			
		//JSONOBJ  
	 int type;            //Node���ͣ���Ϊ��ͨ��ֵ�Ժ�JSON����   
	 char *key;           //��  
	 int keyLength;       //���ַ����ĳ���  
			
	 //key_value          type==JSONTYPE_KV  
	 char *value;     //ֵ  
	 int valueLength;     //ֵ�ַ�������  
	 //JSONARRAY ARRAY    type==JSONTYPE_ARR  
	 int arrayLength; //ֵΪJSON����ʱ����Ԫ�ظ���<span style="font-family: Arial, Helvetica, sans-serif;">             </span>  
	 struct _JSONObjectNode **objectNode; //����  
}JSONNode;  
	
/** 
* JSONObject ��Ҫ����JSON���� 
*/  
typedef struct _JSONObjectNode{  
		//JSONARRAY  
		JSONNode **jsonNode;      //JSON Obj�е�jsonNode����Ҳ����ÿ��JSON�����е����м�ֵ�Զ�������洢  
		int length;                //����ĳ���  
		struct _JSONObjectNode *next;  //ָ����һ��jsonNode�ڵ�  
}JSONObjectNode;  
	
/** 
* JSON�����б� 
*/  
typedef struct _JSONList{  
				JSONNode *start;    
				JSONNode *end;  
				int length;  
}JSONList;  

#endif
