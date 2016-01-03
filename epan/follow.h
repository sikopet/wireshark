/* follow.h
 *
 * Copyright 1998 Mike Hall <mlh@io.com>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef __FOLLOW_H__
#define __FOLLOW_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <epan/packet.h>
#include "ws_symbol_export.h"

#define MAX_IPADDR_LEN	16

typedef enum {
  TCP_STREAM = 0,
  UDP_STREAM,
  MAX_STREAM
} stream_type;

/* With MSVC and a libwireshark.dll, we need a special declaration. */
WS_DLL_PUBLIC gboolean empty_tcp_stream;
WS_DLL_PUBLIC gboolean incomplete_tcp_stream;

typedef struct _tcp_stream_chunk {
  guint8      src_addr[MAX_IPADDR_LEN];
  guint16     src_port;
  guint32     dlen;
  guint32     packet_num;
} tcp_stream_chunk;

/** Build a follow filter based on the current packet's conversation.
 *
 * @param packet_info [in] The current packet.
 * @param append_filter [in] Optional filter to && (AND) to generated one.
 * @return A filter that specifies the conversation. Must be g_free()d
 * the caller.
 */
WS_DLL_PUBLIC
gchar* build_follow_conv_filter( packet_info * packet_info, const char* append_filter);

/** Build a follow filter based on the current TCP/UDP stream index.
 * follow_index() must be called prior to calling this.
 *
 * @return A filter that specifies the current stream. Must be g_free()d
 * the caller.
 */
WS_DLL_PUBLIC
gchar* build_follow_index_filter(stream_type stream);

WS_DLL_PUBLIC
gboolean follow_addr(stream_type, const address *, guint, const address *, guint );

/** Select a TCP/UDP stream to follow via its index.
 *
 * @param stream [in] The stream type to follow(TCP_STREAM or UDP_STREAM)
 * @param addr [in] The stream index to follow.
 * @return TRUE on success, FALSE on failure.
 */
WS_DLL_PUBLIC
gboolean follow_index(stream_type stream, guint32 addr);

/** Get the current TCP/UDP index being followed.
 *
 * @return The current TCP/UDP index. The behavior is undefined
 * if no TCP/UDP stream is being followed.
 */
WS_DLL_PUBLIC
guint32 get_follow_index(stream_type stream);

WS_DLL_PUBLIC
void reset_stream_follow(stream_type stream);

typedef struct {
	guint8		ip_address[2][MAX_IPADDR_LEN];
	guint32		port[2];
	unsigned int	bytes_written[2];
	gboolean        is_ipv6;
} follow_stats_t;

WS_DLL_PUBLIC
void follow_stats(follow_stats_t* stats);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
