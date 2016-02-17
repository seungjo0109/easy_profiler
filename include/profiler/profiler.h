/**
Lightweight profiler library for c++
Copyright(C) 2016  Sergey Yagovtsev

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
/**/

#ifndef ____PROFILER____H_______
#define ____PROFILER____H_______

#define TOKEN_JOIN(x, y) x ## y
#define TOKEN_CONCATENATE(x, y) TOKEN_JOIN(x, y)

#if defined ( WIN32 )
#define __func__ __FUNCTION__
#endif

#define PROFILER_ADD_MARK(name)	profiler::Mark TOKEN_CONCATENATE(unique_profiler_mark_name_,__LINE__)(name);\
									profiler::registerMark(&TOKEN_CONCATENATE(unique_profiler_mark_name_,__LINE__));

#define PROFILER_ADD_MARK_GROUPED(name,block_group)	profiler::Mark TOKEN_CONCATENATE(unique_profiler_mark_name_,__LINE__)(name,block_group);\
														profiler::registerMark(&TOKEN_CONCATENATE(unique_profiler_mark_name_,__LINE__));

#define PROFILER_BEGIN_BLOCK(name)	profiler::Block TOKEN_CONCATENATE(unique_profiler_mark_name_,__LINE__)(name);\
									profiler::registerMark(&TOKEN_CONCATENATE(unique_profiler_mark_name_,__LINE__));

#define PROFILER_BEGIN_BLOCK_GROUPED(name,block_group)	profiler::Block TOKEN_CONCATENATE(unique_profiler_mark_name_,__LINE__)(name,block_group);\
														profiler::registerMark(&TOKEN_CONCATENATE(unique_profiler_mark_name_,__LINE__));

#define PROFILER_BEGIN_FUNCTION_BLOCK PROFILER_BEGIN_BLOCK(__func__)

#define PROFILER_BEGIN_FUNCTION_BLOCK_GROUPED(block_group) PROFILER_BEGIN_BLOCK_GROUPED(__func__,block_group)

#define PROFILER_END_BLOCK profiler::endBlock();

#define PROFILER_ENABLE profiler::setEnabled(true);

#define PROFILER_DISABLE profiler::setEnabled(false);

#include <stdint.h>
#include <cstddef>

#ifdef _WIN32
#ifdef	_BUILD_PROFILER
#define  PROFILER_API		__declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define  PROFILER_API		__declspec(dllimport)
#define EXPIMP_TEMPLATE	 extern
#endif
#else
#define  PROFILER_API
#define EXPIMP_TEMPLATE
#endif




namespace profiler
{
	class Mark;
	class Block;
	
	extern "C"{
		void PROFILER_API registerMark(Mark* _mark);
		void PROFILER_API endBlock();
		void PROFILER_API setEnabled(bool isEnable);

	}

	typedef uint64_t timestamp_t;
	typedef unsigned char color_t;
	
	class PROFILER_API Mark
	{
		protected:
			unsigned char type;
			color_t color;
			timestamp_t begin;
			size_t thread_id;
			const char *name;
			void tick(timestamp_t& stamp);
		public:

			Mark(const char* _name, color_t _color = 0);

	};

	class PROFILER_API Block : public Mark
	{
			timestamp_t end;
		public:
			Block(const char* _name, color_t _color = 0); 
			~Block();
	};
}

#endif
