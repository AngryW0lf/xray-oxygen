#pragma once
#include "xr_collide_defs.h"

// refs
class 	ISpatial;
class 	ICollisionForm;
class 	CObject;

#include "../Include/xrRender/FactoryPtr.h"
#include "../Include/xrRender/ObjectSpaceRender.h"
#include "xrXRC.h"
#include "xrCDB.h"

//-----------------------------------------------------------------------------------------------------------
//Space Area
//-----------------------------------------------------------------------------------------------------------
struct hdrCFORM;
class	XRCDB_API						CObjectSpace
{
private:
	// Debug
    std::recursive_mutex					Lock;
	CDB::MODEL							Static;
	Fbox								m_BoundingVolume;
	xrXRC								xrc;				// MT: dangerous
	collide::rq_results					r_temp;				// MT: dangerous
	xr_vector<ISpatial*>				r_spatial;			// MT: dangerous
public:

	FactoryPtr<IObjectSpaceRender>		*m_pRender;

private:
	bool								_RayTest			( const Fvector &start, const Fvector &dir, float range, collide::rq_target tgt, collide::ray_cache* cache, CObject* ignore_object);
	bool								_RayPick			( const Fvector &start, const Fvector &dir, float range, collide::rq_target tgt, collide::rq_result& R, CObject* ignore_object );
	bool								_RayQuery			( collide::rq_results& dest, const collide::ray_defs& rq, collide::rq_callback* cb, LPVOID user_data, collide::test_callback* tb, CObject* ignore_object);
	bool								_RayQuery2			( collide::rq_results& dest, const collide::ray_defs& rq, collide::rq_callback* cb, LPVOID user_data, collide::test_callback* tb, CObject* ignore_object);
	bool								_RayQuery3			( collide::rq_results& dest, const collide::ray_defs& rq, collide::rq_callback* cb, LPVOID user_data, collide::test_callback* tb, CObject* ignore_object);
public:
										CObjectSpace		( );
										~CObjectSpace		( );

	void								Load				(  CDB::build_callback build_callback  );
	void								Create				(  Fvector*	verts, CDB::TRI* tris, const hdrCFORM &H, CDB::build_callback build_callback, IReader* pFS);
	void								Create				(  Fvector*	verts, CDB::TRI* tris, const hdrCFORM &H, CDB::build_callback build_callback, IWriter* pFS);
	// Occluded/No
	bool								RayTest				( const Fvector &start, const Fvector &dir, float range, collide::rq_target tgt, collide::ray_cache* cache, CObject* ignore_object);

	// Game raypick (nearest) - returns object and addititional params
	bool								RayPick				( const Fvector &start, const Fvector &dir, float range, collide::rq_target tgt, collide::rq_result& R, CObject* ignore_object );

	// General collision query
	bool								RayQuery			( collide::rq_results& dest, const collide::ray_defs& rq, collide::rq_callback* cb, LPVOID user_data, collide::test_callback* tb, CObject* ignore_object);
	bool								RayQuery			( collide::rq_results& dest, ICollisionForm* target, const collide::ray_defs& rq);

	bool								BoxQuery			( Fvector const & 		box_center, 
															  Fvector const & 		box_z_axis,
															  Fvector const & 		box_y_axis,
															  Fvector const	& 		box_sizes,
															  xr_vector<Fvector> *	out_tris );

	int									GetNearest			( xr_vector<CObject*>&	q_nearest, ICollisionForm *obj, float range );
	int									GetNearest			( xr_vector<CObject*>&	q_nearest, const Fvector &point, float range, CObject* ignore_object );
	int									GetNearest			( xr_vector<ISpatial*>& q_spatial, xr_vector<CObject*>&	q_nearest, const Fvector &point, float range, CObject* ignore_object );

	CDB::TRI*							GetStaticTris		() { return Static.get_tris();	}
	Fvector*							GetStaticVerts		() { return Static.get_verts(); }
	CDB::MODEL*							GetStaticModel		() { return &Static;			}

	const Fbox&							GetBoundingVolume	() { return m_BoundingVolume;}

	// Debugging
	void								dbgRender			();
};