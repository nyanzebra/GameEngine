#pragma once

namespace cppe {
	namespace pattern {
		namespace creational {
			class prototype {
			protected:
				prototype() = default;
				virtual ~prototype() = default;

			public:
				prototype(prototype& prototype) = delete;

				virtual prototype* clone() = 0;
				virtual void method() = 0;
			};
		}
	}
}