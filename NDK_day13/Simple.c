
// �ֶ�����ͷ�ļ�
#include "com_novate_ndk_day13_Simple1.h"

JNIEXPORT void JNICALL Java_com_novate_ndk_day13_Simple1_callStaticMethod
(JNIEnv *env, jclass jclz){

	// д jni����ʱ��һ��Ҫ��������д������Ҫ��ȷ���Ŀ����ʲô����Ϊ�������֪������һ��Ҫ��ȡ class��metodID��������ȵ�

	// 2. ��ȡjmethodID
	// (JNIEnv *env, jclass clazz, const char *name, const char *sig); 
	// name: ������ getUUID
	// sig: ����ǩ�� �������� ()Ljava/lang/String; ()�����������ΪgetUUID()����û�в�������������ֱ����()��  Ljava/lang/String;��ʾ����ֵ������String���͵�ȫ����
	jmethodID j_mid = (*env)->GetStaticMethodID(env, jclz, "getUUID", "()Ljava/lang/String;");

	// 1. �����Ŀ���ǣ�����java�еĻ�ȡ getUUID()�ķ����������Ǿ�̬��
	// (JNIEnv *env, jclass clazz, jmethodID methodID, ...);  ...��ʾ���ݵĲ���������java�еĻ�ȡ getUUID()����û�в������������ﲻ��Ҫ����
	// j_uuid���ǵ���getUUID�󣬷��ص�j_uuid
	jstring j_uuid = (*env)->CallStaticObjectMethod(env, jclz, j_mid);

	// �� jstring תΪ c_str
	// (JNIEnv *env, jstring str, jboolean *isCopy);
	char *c_uuid = (*env)->GetStringUTFChars(env,j_uuid,NULL);

	// �ַ�������
	(*env)->ReleaseStringUTFChars(env,j_uuid,c_uuid);
	printf("c_uuid = %s" , c_uuid);
}


JNIEXPORT jobject JNICALL Java_com_novate_ndk_day13_Simple1_createPoint
(JNIEnv *env, jclass jclz){
	// jclz: ��Simple1������ Point


	// 2. ��ȡ point �� class , name = "Point��ȫ����"
	// (JNIEnv *env, const char *name);
	// ����Ҫע�⣺��Ҫ�� ��. ��Ҫ�� б��/
	jclass point_clz = (*env)->FindClass(env , "com/novate/ndk/day13/Point");


	// clazz: ��� clazz�������ܴ���jclz��jclz��Simple1������� clazz����Ҫ���� point ����
	// Ŀ���ǣ����� java ��� point ����
	// һ��Ҫ��������д
	// 1. (JNIEnv *env, jclass clazz, jmethodID methodID, ...);

	// methodID: ���췽����id
	// (JNIEnv *env, jclass clazz, const char *name, const char *sig);
	// ���췽����ͳһ�� <init>�������÷����� Point
	jmethodID j_mid = (*env)->GetMethodID(env , point_clz , "<init>" , "(II)V");
	jobject point = (*env)->NewObject(env, point_clz , j_mid , 11 , 22);  // 11 22�ǿɱ�������Ǹ����췽�����ݵ�2��intֵ


	// ���󣺸� y���¸�ֵ
	/*
	va_list: ��������Ǽ���
	void (JNICALL *CallVoidMethodV)
		(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);

	jvalue
	void (JNICALL *CallVoidMethodA)
		(JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);
	*/

	// (JNIEnv *env, jclass clazz, const char *name, const char *sig);
	// name�������� setY
	// sig: ����ǩ�� (I)V , (I)��ʾ������int���ͣ�����ֵû�У���void���͵�
	j_mid = (*env)->GetMethodID(env, point_clz,"setY","(I)V");
	(*env)->CallVoidMethod(env , point , j_mid);

	return point;

	// д������֮�󣬾� ���� - �������ɽ��������Ȼ������java ����
	// ע�⣺ÿ�޸�һ��VS���룬�� ���� - �������ɽ��������Ȼ������java ����
}

void main(){
	// ������ �����֮�����޸�
	const int number = 100;
	// number = 200;
	int number1 = 100;
	int number2 = 200;

	/*// ����ָ��
	const int* n_p = &number2;  // int const* n_p = &number2; ����Ҳ�ǿ��Եģ�ֻҪconst�� *֮ǰ�Ϳ���
	// n_p��ָ�룬��number1�ĵ�ַ��ֵ�� n_pָ��
	n_p = &number1;
	printf("n_p = %p" , n_p); // ��ַ�ǿ������±���ֵ��
	// �Ե�ַȡֵ
	// *n_p = 300; ֵ�����޸�*/

	// ָ�볣��
	int *const n_p = &number2;
	// n_p��ָ�룬���ܸ�n_p��ַ���¸�ֵ���ᱨ��
	// n_p = &number1;  
	*n_p = 300;
	printf("number2 = %d" , number2);  // number2 = 300
	getchar();

}