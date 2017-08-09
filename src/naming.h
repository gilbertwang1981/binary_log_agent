#ifndef __NAMING_H__
#define __NAMING_H__

namespace binlog {
	class NamingService {
		public:
			NamingService();
			~NamingService();

			static NamingService * instance();

			bool initialize(void);

			static bool callback(char * buffer , int & length);

		private:
			static NamingService * m_instance;
	};
}

#endif


