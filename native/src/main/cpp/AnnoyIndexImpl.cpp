#include "annoylib.h"
#include "kissrandom.h"
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

jlong Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppCtor(JNIEnv *env, jobject obj, jint dim, jint metric)
{
	try {
		switch (metric)
		{
		case 'a':
			return (jlong) new AnnoyIndex<int, float, Angular, Kiss32Random>(dim);
		case 'e':
			return (jlong) new AnnoyIndex<int, float, Euclidean, Kiss32Random>(dim);
		case 'm':
			return (jlong) new AnnoyIndex<int, float, Manhattan, Kiss32Random>(dim);
		case 'd':
			return (jlong) new AnnoyIndex<int, float, DotProduct, Kiss32Random>(dim);
		}
	} catch (const std::exception &e) {
		fprintf(stderr, "exception when trying to create new C++ AnnoyIndex: %s", e.what());
		return (jlong) NULL;
	}

	return (jlong) NULL;
}

void Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppDtor(JNIEnv *env, jobject obj, jlong cppPtr)
{
	// this works well, because AnnoyIndexInterface destructor is virtual
	delete (AnnoyIndexInterface<int, float> *) cppPtr;
}

void Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppAddItem(JNIEnv *env, jobject obj, jlong cppPtr, jint item, jfloatArray vector)
{
	// TODO implement
}

jintArray Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppGetNearestByVector(JNIEnv *env, jobject obj, jlong cppPtr, jfloatArray vector, jint nbNeighbors)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;

	float *vectorCpp = env->GetFloatArrayElements(vector, NULL);

	std::vector<int> result;
	ann->get_nns_by_vector(vectorCpp, nbNeighbors, -1, &result, NULL);

	jintArray resultJni = env->NewIntArray(result.size());
	jint *resultJniElements = env->GetIntArrayElements(resultJni, NULL);

	for (size_t i = 0; i < result.size(); ++i)
	{
		resultJniElements[i] = result[i];
	}

	env->ReleaseIntArrayElements(resultJni, resultJniElements, 0);
	env->ReleaseFloatArrayElements(vector, vectorCpp, 0);

	return resultJni;
}

jintArray Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppGetNearestByVectorK(JNIEnv *env, jobject obj, jlong cppPtr, jfloatArray vector, jint nbNeighbors, jint searchK)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;

	float *vectorCpp = env->GetFloatArrayElements(vector, NULL);

	std::vector<int> result;
	ann->get_nns_by_vector(vectorCpp, nbNeighbors, searchK, &result, NULL);

	jintArray resultJni = env->NewIntArray(result.size());
	jint *resultJniElements = env->GetIntArrayElements(resultJni, NULL);

	for (size_t i = 0; i < result.size(); ++i)
	{
		resultJniElements[i] = result[i];
	}

	env->ReleaseIntArrayElements(resultJni, resultJniElements, 0);
	env->ReleaseFloatArrayElements(vector, vectorCpp, 0);

	return resultJni;
}

jintArray Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppGetNearestByItem(JNIEnv *env, jobject obj, jlong cppPtr, jint item, jint nbNeighbors)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;

	std::vector<int> result;
	ann->get_nns_by_item(item, nbNeighbors, -1, &result, NULL);

	jintArray resultJni = env->NewIntArray(result.size());
	jint *resultJniElements = env->GetIntArrayElements(resultJni, NULL);

	for (size_t i = 0; i < result.size(); ++i)
	{
		resultJniElements[i] = result[i];
	}

	env->ReleaseIntArrayElements(resultJni, resultJniElements, 0);

	return resultJni;
}

jintArray Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppGetNearestByItemK(JNIEnv *env, jobject obj, jlong cppPtr, jint item, jint nbNeighbors, jint searchK)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;

	std::vector<int> result;
	ann->get_nns_by_item(item, nbNeighbors, searchK, &result, NULL);

	jintArray resultJni = env->NewIntArray(result.size());
	jint *resultJniElements = env->GetIntArrayElements(resultJni, NULL);

	for (size_t i = 0; i < result.size(); ++i)
	{
		resultJniElements[i] = result[i];
	}

	env->ReleaseIntArrayElements(resultJni, resultJniElements, 0);

	return resultJni;
}

void Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppBuild(JNIEnv *env, jobject obj, jlong cppPtr, jint nbTrees)
{
	// TODO implement
}

void Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppSave(JNIEnv *env, jobject obj, jlong cppPtr, jstring filename)
{
	// TODO implement
}

void Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppLoad(JNIEnv *env, jobject obj, jlong cppPtr, jstring filename)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;
	const char *filenameCpp = env->GetStringUTFChars(filename, NULL);
	ann->load(filenameCpp);
	env->ReleaseStringUTFChars(filename, filenameCpp);
}

jfloatArray Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppGetItemVector(JNIEnv *env, jobject obj, jlong cppPtr, jint dim, jint item)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;

	float *vector = new float[dim];
	ann->get_item(item, vector);

	jfloatArray resultJni = env->NewFloatArray(dim);
	jfloat *resultJniElements = env->GetFloatArrayElements(resultJni, NULL);

	for (size_t i = 0; i < dim; ++i)
	{
		resultJniElements[i] = vector[i];
	}

	env->ReleaseFloatArrayElements(resultJni, resultJniElements, 0);
	delete[] vector;

	return resultJni;
}

jfloat Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppGetDistance(JNIEnv *env, jobject obj, jlong cppPtr, jint itemA, jint itemB)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;
	return ann->get_distance(itemA, itemB);
}

jint Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppSize(JNIEnv *env, jobject obj, jlong cppPtr)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;
	return ann->get_n_items();
}

void Java_com_spotify_annoy_jni_base_AnnoyIndexImpl_cppSetSeed(JNIEnv *env, jobject obj, jlong cppPtr, jint seed)
{
	AnnoyIndexInterface<int, float> *ann = (AnnoyIndexInterface<int, float> *) cppPtr;
	ann->set_seed(seed);
}

#ifdef __cplusplus
}
#endif
