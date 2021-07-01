// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMesh.h"

#include "KismetProceduralMeshLibrary.h"
#include "UE_Assimp.h"

void UAIMesh::GetMeshVertices(TArray<FVector>& Vertices)
{

	if(!this)
	{
		UE_LOG(LogTemp,Fatal,TEXT("No Mesh"));
		return;
	}
	if(!Mesh)
	{
		UE_LOG(LogTemp,Fatal,TEXT("No Mesh Data"));
		return;
	}
Vertices.Empty();
Vertices.AddUninitialized(Mesh->mNumVertices);
for (unsigned int Index=0;Index<Mesh->mNumVertices;Index++)
{
	Vertices[Index]= ToVector(Mesh->mVertices[Index]);
	
}
	
}

void UAIMesh::GetMeshNormals(TArray<FVector>& Normals)
{
	if(!this)
	{
		UE_LOG(LogTemp,Fatal,TEXT("No Mesh"));
		return;
	}
	if(!Mesh)
	{
		UE_LOG(LogTemp,Fatal,TEXT("No Mesh Data"));
		return;
	}
	Normals.Empty();
	Normals.AddUninitialized(Mesh->mNumVertices);
	for (unsigned int Index=0;Index<Mesh->mNumVertices;Index++)
	{
		Normals[Index]= ToVector(Mesh->mNormals[Index]);
		
	}
}

void UAIMesh::GetMeshDataForProceduralMesh(TArray<FVector>& Vertices, TArray<int32>& Triangles,
	TArray<FVector>& Normals, TArray<FVector2D>& UV0,  TArray<FProcMeshTangent>& Tangents)
{


	
	if(!this)
	{
		UE_LOG(LogTemp,Fatal,TEXT("No Mesh"));
		return;
	}
	if(!Mesh)
	{
		UE_LOG(LogTemp,Fatal,TEXT("No Mesh Data"));
		return;
	}

	Tangents.Reset();
	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();

	Vertices.AddUninitialized(Mesh->mNumVertices);
	Normals.AddUninitialized(Mesh->mNumVertices);
	Tangents.AddUninitialized(Mesh->mNumVertices);
	
	for (unsigned int Index=0;Index<Mesh->mNumVertices;Index++)
	{
		Normals[Index]= ToVector(Mesh->mNormals[Index]);
		Vertices[Index]=ToVectorCM(Mesh->mVertices[Index]);
		Tangents[Index].TangentX=ToVector(Mesh->mTangents[Index]);
		
	}


	
	for (unsigned int  i = 0; i < Mesh->mNumFaces; i++) {
		auto face = Mesh->mFaces[i];
		for (unsigned index = 0; index < face.mNumIndices; index++) {
			Triangles.Push(face.mIndices[index]);
		}
	}


	
}

int UAIMesh::GetNumVertices()
{
	return Mesh->mNumVertices;
}


UAIMesh* UAIMesh::InternalConstructNewAIMesh(aiMesh* InMesh, UObject* Parent)
{
	

	//todo check if object is already created and skip creation and return object
	//should be owned by AIScene object
	if(!InMesh)
	{
		UE_LOG(LogTemp,Fatal,TEXT(" No assimp Mesh data  Found "))
		return nullptr;
	}else
	{
		UAIMesh* NewMeshData=	NewObject<UAIMesh>(Parent,UAIMesh::StaticClass(),NAME_None,RF_Transient);
		NewMeshData->Mesh=InMesh;
		return NewMeshData;
	}

	
}
