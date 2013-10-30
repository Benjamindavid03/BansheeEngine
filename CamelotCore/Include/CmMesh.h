#pragma once

#include "CmPrerequisites.h"
#include "CmGpuResource.h"
#include "CmMeshData.h"
#include "CmVertexData.h"
#include "CmIndexData.h"
#include "CmDrawOps.h"

namespace CamelotFramework
{
	struct CM_EXPORT SubMesh
	{
		SubMesh()
			: indexOffset(0), indexCount(0), drawOp(DOT_TRIANGLE_LIST), 
			vertexData(nullptr), indexData(nullptr), useIndexes(true)
		{ }

		SubMesh(UINT32 indexOffset, UINT32 indexCount, DrawOperationType drawOp, 
			std::shared_ptr<VertexData> vertexData, std::shared_ptr<IndexData> indexData, bool useIndexes):
			indexOffset(indexOffset), indexCount(indexCount), drawOp(drawOp),
			vertexData(vertexData), indexData(indexData), useIndexes(useIndexes)
		{ }

		UINT32 indexOffset;
		UINT32 indexCount;
		DrawOperationType drawOp;

		std::shared_ptr<VertexData> vertexData;
		std::shared_ptr<IndexData> indexData;

		bool useIndexes;
	};

	class CM_EXPORT Mesh : public GpuResource
	{
	public:
		virtual ~Mesh();

		/**
		 * @copydoc GpuResource::writeSubresource
		 */
		virtual void writeSubresource(UINT32 subresourceIdx, const GpuResourceData& data);

		/**
		 * @copydoc GpuResource::readSubresource
		 */
		virtual void readSubresource(UINT32 subresourceIdx, GpuResourceData& data);

		/**
		 * @brief	Allocates a buffer you may use for storage when reading a subresource. You
		 * 			need to allocate such a buffer if you are calling "readSubresource".
		 * 			
		 * @note	This method is thread safe.
		 */
		MeshDataPtr allocateSubresourceBuffer(UINT32 subresourceIdx) const;

		/**
		 * @brief	TODO - Currently does nothing. But normally it should provide a way to map subresource index to
		 * 			a specific submesh or buffer stream. Right now you can only work with entire mesh at once, not its subsets.
		 */
		void mapFromSubresourceIdx(UINT32 subresourceIdx) const {}

		/**
		 * @brief	TODO - Currently does nothing. But normally it should provide a way to map submesh or stream index to
		 * 			a specific subresource index. Right now you can only work with entire mesh at once, not its subsets.
		 */
		UINT32 mapToSubresourceIdx() const { return 0; }

		const SubMesh& getSubMesh(UINT32 subMeshIdx = 0) const;
		UINT32 getNumSubMeshes() const { return (UINT32)mSubMeshes.size(); }

		const AABox& getBounds() const;
		const AABox& getBounds(UINT32 submeshIdx) const;

		/**
		 * @brief	Returns a dummy mesh, containing just one triangle. Don't modify the returned mesh.
		 */
		static HMesh dummy();

	protected:
		friend class MeshManager;

		Mesh();

		std::shared_ptr<VertexData> mVertexData;
		std::shared_ptr<IndexData> mIndexData;

		Vector<SubMesh>::type mSubMeshes;

		/**
		 * @copydoc Resource::initialize_internal()
		 */
		virtual void initialize_internal();

		/**
		 * @copydoc Resource::destroy_internal()
		 */
		virtual void destroy_internal();

		/************************************************************************/
		/* 								SERIALIZATION                      		*/
		/************************************************************************/
	public:
		friend class MeshRTTI;
		static RTTITypeBase* getRTTIStatic();
		virtual RTTITypeBase* getRTTI() const;

		/************************************************************************/
		/* 								STATICS		                     		*/
		/************************************************************************/
		
	public:
		static HMesh create();
	};
}