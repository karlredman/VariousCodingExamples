EXTRA_DIST = class_SocketBase.h class_TCPClient.h class_TCPServer.h class_UDP.h class_UDPClient.h class_UDPServer.h class_MCast.h class_MCastServer.h class_MCastClient.h
#
INCLUDES = -I$(top_srcdir)/include
LDFLAGS = -L$(top_srcdir)/lib
CPPFLAGS = -g -Wall
#
bin_PROGRAMS = TCPServer TCPClient UDPServer UDPClient MCastServer MCastClient
#
TCPServer_SOURCES = \
	class_SocketBase.C \
	class_TCPSocket.C \
	class_TCPServer.C \
	TCPServer.C
#
TCPClient_SOURCES = \
	class_SocketBase.C \
	class_TCPSocket.C \
	class_TCPClient.C \
        TCPClient.C 
#
UDPServer_SOURCES = \
	class_SocketBase.C \
	class_UDP.C \
	class_UDPServer.C \
	UDPServer.C
#
UDPClient_SOURCES = \
	class_SocketBase.C \
	class_UDP.C \
	class_UDPClient.C \
	UDPClient.C
#
MCastServer_SOURCES = \
	class_SocketBase.C \
	class_UDP.C \
	class_MCast.C \
	class_MCastServer.C \
	MCastServer.C 
#
MCastClient_SOURCES = \
	class_SocketBase.C \
	class_UDP.C \
	class_MCast.C \
	class_MCastClient.C \
	MCastClient.C 
