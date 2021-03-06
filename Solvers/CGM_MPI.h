#pragma once

#include <cstdlib>
#include "Utils/FDMGridMPI.h"
#include <mpi.h>

class sparse_matrix;
class vector;

namespace Solvers
{
	class cgm_mpi
	{
	private:
		typedef fdm_grid_mpi::side_index side_index;
		struct boundaries_list
		{
			int nProcessRank;
			MPI_Datatype send_t;
			MPI_Datatype receive_t;
		};

	private:
		std::vector<boundaries_list> m_vBoundaryProcs;
		std::vector<std::vector<size_t>> m_vNeighbours;
		std::vector<bool> m_vBoundFlag;

	private:
		void update_boundaries(vector &vSolution, vector &vRightPartDelta) const;
		void create_datatype(std::vector<int> indexes, MPI_Datatype *datatype) const;

		template < typename T >
		std::ostream& print_vector(const T &vArr, int nIndDisplace = 0, int nMaxInd = -1, const std::string &sPrefix = "",
		                           bool bOutIndex=false, const std::string &sDelim = "\t") const;

	public:
		cgm_mpi(const std::vector<fdm_grid_mpi::boundaries_list> &vBoundaryProcs,
				        const std::vector<std::vector<size_t>> &vNeighbours, const std::vector<bool> &vBoundFlag);
		size_t solve(const sparse_matrix &mA, vector &vSol, const vector &vRightPart, double rEps, int nMaxIter);

		void update_right_part(const std::vector<double> &vBoundaryValues, vector &vRightPartDelta) const;
	};
}
