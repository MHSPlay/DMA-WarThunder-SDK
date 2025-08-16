#pragma once

class c_camera {
public:
	auto init( uintptr_t cGame ) -> bool {
		this->base_address = TargetProcess->Read< uintptr_t >( cGame + offsets::cgame_offsets::camera_offset );
		return this->base_address != 0;
	}

public:

	auto getCameraMatrix( ) -> ViewMatrix_t {

		//return TargetProcess->Read< ViewMatrix_t >( this->base_address + offsets::cgame_offsets::camera_offsets::camera_matrix_offset );

		VMMDLL_SCATTER_HANDLE hScatter = TargetProcess->CreateScatterHandle( );
		if ( !hScatter )
			return ViewMatrix_t( );

		ViewMatrix_t matrix;
		if (!TargetProcess->AddScatterReadRequest( hScatter, uintptr_t( this->base_address + offsets::cgame_offsets::camera_offsets::camera_matrix_offset ), &matrix, sizeof( ViewMatrix_t ) ) || !TargetProcess->ExecuteReadScatter( hScatter, 0, true ) ) {
			TargetProcess->CloseScatterHandle( hScatter );
			return ViewMatrix_t( );
		}

		return matrix;
	}

private:
	uintptr_t base_address;
};
