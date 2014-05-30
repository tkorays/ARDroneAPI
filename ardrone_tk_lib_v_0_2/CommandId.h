#ifndef _TK_COMMAND_ID_H_
#define _TK_COMMAND_ID_H_
#pragma once

namespace tk {
	class CommandId {
	private:
		long id;
	public:
		CommandId();
		void inc();
		void operator++();
		void reset();
		long get_id(bool auto_inc=true);
	};
}

#endif // _TK_COMMAND_ID_H_