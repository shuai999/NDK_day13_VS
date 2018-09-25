
// 手动引入头文件
#include "com_novate_ndk_day13_Simple1.h"

JNIEXPORT void JNICALL Java_com_novate_ndk_day13_Simple1_callStaticMethod
(JNIEnv *env, jclass jclz){

	// 写 jni代码时，一定要从下往上写，首先要明确你的目的是什么，因为你根本不知道我下一步要获取 class、metodID、还是类等等

	// 2. 获取jmethodID
	// (JNIEnv *env, jclass clazz, const char *name, const char *sig); 
	// name: 方法名 getUUID
	// sig: 方法签名 用命令行 ()Ljava/lang/String; ()代表参数，因为getUUID()方法没有参数，所以这里直接是()；  Ljava/lang/String;表示返回值类型是String类型的全类名
	jmethodID j_mid = (*env)->GetStaticMethodID(env, jclz, "getUUID", "()Ljava/lang/String;");

	// 1. 这里的目的是：调用java中的获取 getUUID()的方法，而且是静态的
	// (JNIEnv *env, jclass clazz, jmethodID methodID, ...);  ...表示传递的参数，由于java中的获取 getUUID()方法没有参数，所以这里不需要传递
	// j_uuid就是调用getUUID后，返回的j_uuid
	jstring j_uuid = (*env)->CallStaticObjectMethod(env, jclz, j_mid);

	// 把 jstring 转为 c_str
	// (JNIEnv *env, jstring str, jboolean *isCopy);
	char *c_uuid = (*env)->GetStringUTFChars(env,j_uuid,NULL);

	// 字符串回收
	(*env)->ReleaseStringUTFChars(env,j_uuid,c_uuid);
	printf("c_uuid = %s" , c_uuid);
}


JNIEXPORT jobject JNICALL Java_com_novate_ndk_day13_Simple1_createPoint
(JNIEnv *env, jclass jclz){
	// jclz: 是Simple1，不是 Point


	// 2. 获取 point 的 class , name = "Point的全类名"
	// (JNIEnv *env, const char *name);
	// 这里要注意：不要用 点. ，要用 斜杠/
	jclass point_clz = (*env)->FindClass(env , "com/novate/ndk/day13/Point");


	// clazz: 这个 clazz参数不能传递jclz，jclz是Simple1，而这个 clazz是需要传递 point 对象
	// 目的是：构建 java 层的 point 对象
	// 一定要从下往上写
	// 1. (JNIEnv *env, jclass clazz, jmethodID methodID, ...);

	// methodID: 构造方法的id
	// (JNIEnv *env, jclass clazz, const char *name, const char *sig);
	// 构造方法，统一用 <init>，不能用方法名 Point
	jmethodID j_mid = (*env)->GetMethodID(env , point_clz , "<init>" , "(II)V");
	jobject point = (*env)->NewObject(env, point_clz , j_mid , 11 , 22);  // 11 22是可变参数，是给构造方法传递的2个int值


	// 需求：给 y重新赋值
	/*
	va_list: 这个参数是集合
	void (JNICALL *CallVoidMethodV)
		(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);

	jvalue
	void (JNICALL *CallVoidMethodA)
		(JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);
	*/

	// (JNIEnv *env, jclass clazz, const char *name, const char *sig);
	// name：方法名 setY
	// sig: 方法签名 (I)V , (I)表示参数是int类型，返回值没有，是void类型的
	j_mid = (*env)->GetMethodID(env, point_clz,"setY","(I)V");
	(*env)->CallVoidMethod(env , point , j_mid);

	return point;

	// 写到这里之后，就 生成 - 重新生成解决方案，然后运行java 代码
	// 注意：每修改一次VS代码，都 生成 - 重新生成解决方案，然后运行java 代码
}

void main(){
	// 常量： 定义好之后不能修改
	const int number = 100;
	// number = 200;
	int number1 = 100;
	int number2 = 200;

	/*// 常量指针
	const int* n_p = &number2;  // int const* n_p = &number2; 这样也是可以的，只要const在 *之前就可以
	// n_p是指针，把number1的地址赋值给 n_p指针
	n_p = &number1;
	printf("n_p = %p" , n_p); // 地址是可以重新被赋值的
	// 对地址取值
	// *n_p = 300; 值不能修改*/

	// 指针常量
	int *const n_p = &number2;
	// n_p是指针，不能给n_p地址重新赋值，会报错
	// n_p = &number1;  
	*n_p = 300;
	printf("number2 = %d" , number2);  // number2 = 300
	getchar();

}