// SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright Authors of Cilium */

#include <bpf/ctx/xdp.h>
#include <bpf/api.h>

#include <node_config.h>
#include <netdev_config.h>
#include <filter_config.h>

#define SKIP_POLICY_MAP 1

/* Controls the inclusion of the CILIUM_CALL_HANDLE_ICMP6_NS section in the
 * bpf_lxc object file.
 */
#define SKIP_ICMPV6_NS_HANDLING

/* Controls the inclusion of the CILIUM_CALL_SEND_ICMP6_TIME_EXCEEDED section
 * in the bpf_lxc object file. This is needed for all callers of
 * ipv6_local_delivery, which calls into the IPv6 L3 handling.
 */
#define SKIP_ICMPV6_HOPLIMIT_HANDLING

/* Controls the inclusion of the CILIUM_CALL_SEND_ICMP6_ECHO_REPLY section in
 * the bpf_lxc object file.
 */
#define SKIP_ICMPV6_ECHO_HANDLING

/* Controls the inclusion of the CILIUM_CALL_SRV6 section in the object file.
 */
#define SKIP_SRV6_HANDLING

/* The XDP datapath does not take care of health probes from the local node,
 * thus do not compile it in.
 */
#undef ENABLE_HEALTH_CHECK

#include "lib/common.h"
#include "lib/maps.h"
#include "lib/eps.h"
#include "lib/events.h"
#include "lib/nodeport.h"

#ifdef ENABLE_PREFILTER
#ifndef HAVE_LPM_TRIE_MAP_TYPE
# undef CIDR4_LPM_PREFILTER
# undef CIDR6_LPM_PREFILTER
#endif

#ifdef CIDR4_FILTER
struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, struct lpm_v4_key);
	__type(value, struct lpm_val);
	__uint(pinning, LIBBPF_PIN_BY_NAME);
	__uint(max_entries, CIDR4_HMAP_ELEMS);
	__uint(map_flags, BPF_F_NO_PREALLOC);
} CIDR4_HMAP_NAME __section_maps_btf;

#ifdef CIDR4_LPM_PREFILTER
struct {
	__uint(type, BPF_MAP_TYPE_LPM_TRIE);
	__type(key, struct lpm_v4_key);
	__type(value, struct lpm_val);
	__uint(pinning, LIBBPF_PIN_BY_NAME);
	__uint(max_entries, CIDR4_LMAP_ELEMS);
	__uint(map_flags, BPF_F_NO_PREALLOC);
} CIDR4_LMAP_NAME __section_maps_btf;

#endif /* CIDR4_LPM_PREFILTER */
#endif /* CIDR4_FILTER */

#ifdef CIDR6_FILTER
struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, struct lpm_v6_key);
	__type(value, struct lpm_val);
	__uint(pinning, LIBBPF_PIN_BY_NAME);
	__uint(max_entries, CIDR4_HMAP_ELEMS);
	__uint(map_flags, BPF_F_NO_PREALLOC);
} CIDR6_HMAP_NAME __section_maps_btf;

#ifdef CIDR6_LPM_PREFILTER
struct {
	__uint(type, BPF_MAP_TYPE_LPM_TRIE);
	__type(key, struct lpm_v6_key);
	__type(value, struct lpm_val);
	__uint(pinning, LIBBPF_PIN_BY_NAME);
	__uint(max_entries, CIDR4_LMAP_ELEMS);
	__uint(map_flags, BPF_F_NO_PREALLOC);
} CIDR6_LMAP_NAME __section_maps_btf;
#endif /* CIDR6_LPM_PREFILTER */
#endif /* CIDR6_FILTER */
#endif /* ENABLE_PREFILTER */

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 96,
  "endLine": 117,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "bpf_xdp_exit",
  "developer_inline_comments": [
    {
      "start_line": 1,
      "end_line": 1,
      "text": "// SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause)"
    },
    {
      "start_line": 2,
      "end_line": 2,
      "text": "/* Copyright Authors of Cilium */"
    },
    {
      "start_line": 13,
      "end_line": 15,
      "text": "/* Controls the inclusion of the CILIUM_CALL_HANDLE_ICMP6_NS section in the\n * bpf_lxc object file.\n */"
    },
    {
      "start_line": 18,
      "end_line": 21,
      "text": "/* Controls the inclusion of the CILIUM_CALL_SEND_ICMP6_TIME_EXCEEDED section\n * in the bpf_lxc object file. This is needed for all callers of\n * ipv6_local_delivery, which calls into the IPv6 L3 handling.\n */"
    },
    {
      "start_line": 24,
      "end_line": 26,
      "text": "/* Controls the inclusion of the CILIUM_CALL_SEND_ICMP6_ECHO_REPLY section in\n * the bpf_lxc object file.\n */"
    },
    {
      "start_line": 29,
      "end_line": 30,
      "text": "/* Controls the inclusion of the CILIUM_CALL_SRV6 section in the object file.\n */"
    },
    {
      "start_line": 33,
      "end_line": 35,
      "text": "/* The XDP datapath does not take care of health probes from the local node,\n * thus do not compile it in.\n */"
    },
    {
      "start_line": 70,
      "end_line": 70,
      "text": "/* CIDR4_LPM_PREFILTER */"
    },
    {
      "start_line": 71,
      "end_line": 71,
      "text": "/* CIDR4_FILTER */"
    },
    {
      "start_line": 92,
      "end_line": 92,
      "text": "/* CIDR6_LPM_PREFILTER */"
    },
    {
      "start_line": 93,
      "end_line": 93,
      "text": "/* CIDR6_FILTER */"
    },
    {
      "start_line": 94,
      "end_line": 94,
      "text": "/* ENABLE_PREFILTER */"
    },
    {
      "start_line": 102,
      "end_line": 104,
      "text": "/* We transfer data from XFER_MARKER. This specifically\n\t\t * does not break packet trains in GRO.\n\t\t */"
    }
  ],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx",
    " const int verdict"
  ],
  "output": "static__always_inline__maybe_unusedint",
  "helper": [
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "xdp",
    "sched_act",
    "sched_cls"
  ],
  "source": [
    "static __always_inline __maybe_unused int bpf_xdp_exit (struct  __ctx_buff *ctx, const int verdict)\n",
    "{\n",
    "    if (verdict == CTX_ACT_OK) {\n",
    "        __u32 meta_xfer = ctx_load_meta (ctx, XFER_MARKER);\n",
    "        if (meta_xfer) {\n",
    "            if (!ctx_adjust_meta (ctx, -(int) sizeof (meta_xfer))) {\n",
    "                __u32 *data_meta = ctx_data_meta (ctx);\n",
    "                __u32 *data = ctx_data (ctx);\n",
    "                if (!ctx_no_room (data_meta + 1, data))\n",
    "                    data_meta[0] = meta_xfer;\n",
    "            }\n",
    "        }\n",
    "    }\n",
    "    return verdict;\n",
    "}\n"
  ],
  "called_function_list": [
    "ctx_load_meta",
    "ctx_data",
    "ctx_adjust_meta",
    "ctx_no_room",
    "ctx_data_meta"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline __maybe_unused int
bpf_xdp_exit(struct __ctx_buff *ctx, const int verdict)
{
	if (verdict == CTX_ACT_OK) {
		__u32 meta_xfer = ctx_load_meta(ctx, XFER_MARKER);

		/* We transfer data from XFER_MARKER. This specifically
		 * does not break packet trains in GRO.
		 */
		if (meta_xfer) {
			if (!ctx_adjust_meta(ctx, -(int)sizeof(meta_xfer))) {
				__u32 *data_meta = ctx_data_meta(ctx);
				__u32 *data = ctx_data(ctx);

				if (!ctx_no_room(data_meta + 1, data))
					data_meta[0] = meta_xfer;
			}
		}
	}

	return verdict;
}

#ifdef ENABLE_IPV4
#ifdef ENABLE_NODEPORT_ACCELERATION
__section_tail(CILIUM_MAP_CALLS, CILIUM_CALL_IPV4_FROM_NETDEV)
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 122,
  "endLine": 140,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "tail_lb_ipv4",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "int",
  "helper": [
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "xdp",
    "sched_act",
    "sched_cls"
  ],
  "source": [
    "int tail_lb_ipv4 (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    int ret = CTX_ACT_OK;\n",
    "    if (!bpf_skip_nodeport (ctx)) {\n",
    "        ret = nodeport_lb4 (ctx, 0);\n",
    "        if (ret == NAT_46X64_RECIRC) {\n",
    "            ep_tail_call (ctx, CILIUM_CALL_IPV6_FROM_NETDEV);\n",
    "            return send_drop_notify_error (ctx, 0, DROP_MISSED_TAIL_CALL, CTX_ACT_DROP, METRIC_INGRESS);\n",
    "        }\n",
    "        else if (IS_ERR (ret)) {\n",
    "            return send_drop_notify_error (ctx, 0, ret, CTX_ACT_DROP, METRIC_INGRESS);\n",
    "        }\n",
    "    }\n",
    "    return bpf_xdp_exit (ctx, ret);\n",
    "}\n"
  ],
  "called_function_list": [
    "ep_tail_call",
    "IS_ERR",
    "bpf_xdp_exit",
    "bpf_skip_nodeport",
    "nodeport_lb4",
    "send_drop_notify_error"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
int tail_lb_ipv4(struct __ctx_buff *ctx)
{
	int ret = CTX_ACT_OK;

	if (!bpf_skip_nodeport(ctx)) {
		ret = nodeport_lb4(ctx, 0);
		if (ret == NAT_46X64_RECIRC) {
			ep_tail_call(ctx, CILIUM_CALL_IPV6_FROM_NETDEV);
			return send_drop_notify_error(ctx, 0, DROP_MISSED_TAIL_CALL,
						      CTX_ACT_DROP,
						      METRIC_INGRESS);
		} else if (IS_ERR(ret)) {
			return send_drop_notify_error(ctx, 0, ret, CTX_ACT_DROP,
						      METRIC_INGRESS);
		}
	}

	return bpf_xdp_exit(ctx, ret);
}

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 142,
  "endLine": 147,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_v4_lb",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlineint",
  "helper": [],
  "compatibleHookpoints": [
    "lwt_xmit",
    "lwt_out",
    "lwt_seg6local",
    "sk_skb",
    "sched_cls",
    "socket_filter",
    "sk_reuseport",
    "sk_msg",
    "kprobe",
    "xdp",
    "cgroup_skb",
    "raw_tracepoint_writable",
    "lwt_in",
    "perf_event",
    "cgroup_sock",
    "cgroup_sock_addr",
    "raw_tracepoint",
    "flow_dissector",
    "cgroup_sysctl",
    "sock_ops",
    "tracepoint",
    "sched_act",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline int check_v4_lb (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    ep_tail_call (ctx, CILIUM_CALL_IPV4_FROM_NETDEV);\n",
    "    return send_drop_notify_error (ctx, 0, DROP_MISSED_TAIL_CALL, CTX_ACT_DROP, METRIC_INGRESS);\n",
    "}\n"
  ],
  "called_function_list": [
    "send_drop_notify_error",
    "ep_tail_call"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_v4_lb(struct __ctx_buff *ctx)
{
	ep_tail_call(ctx, CILIUM_CALL_IPV4_FROM_NETDEV);
	return send_drop_notify_error(ctx, 0, DROP_MISSED_TAIL_CALL, CTX_ACT_DROP,
				      METRIC_INGRESS);
}
#else
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 149,
  "endLine": 152,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_v4_lb",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff * ctx __maybe_unused"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "xdp",
    "sched_act",
    "sched_cls"
  ],
  "source": [
    "static __always_inline int check_v4_lb (struct  __ctx_buff * ctx __maybe_unused)\n",
    "{\n",
    "    return CTX_ACT_OK;\n",
    "}\n"
  ],
  "called_function_list": [
    "send_drop_notify_error",
    "ep_tail_call"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_v4_lb(struct __ctx_buff *ctx __maybe_unused)
{
	return CTX_ACT_OK;
}
#endif /* ENABLE_NODEPORT_ACCELERATION */

#ifdef ENABLE_PREFILTER
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "map_read",
      "map_read": [
        {
          "Project": "cilium",
          "Return Type": "void*",
          "Description": "Perform a lookup in <[ map ]>(IP: 0) for an entry associated to key. ",
          "Return": " Map value associated to key, or NULL if no entry was found.",
          "Function Name": "map_lookup_elem",
          "Input Params": [
            "{Type: struct map ,Var: *map}",
            "{Type:  const void ,Var: *key}"
          ],
          "compatible_hookpoints": [
            "socket_filter",
            "kprobe",
            "sched_cls",
            "sched_act",
            "tracepoint",
            "xdp",
            "perf_event",
            "cgroup_skb",
            "cgroup_sock",
            "lwt_in",
            "lwt_out",
            "lwt_xmit",
            "sock_ops",
            "sk_skb",
            "cgroup_device",
            "sk_msg",
            "raw_tracepoint",
            "cgroup_sock_addr",
            "lwt_seg6local",
            "sk_reuseport",
            "flow_dissector",
            "cgroup_sysctl",
            "raw_tracepoint_writable"
          ],
          "capabilities": [
            "map_read"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 156,
  "endLine": 179,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_v4",
  "developer_inline_comments": [
    {
      "start_line": 173,
      "end_line": 173,
      "text": "/* CIDR4_LPM_PREFILTER */"
    },
    {
      "start_line": 178,
      "end_line": 178,
      "text": "/* CIDR4_FILTER */"
    }
  ],
  "updateMaps": [],
  "readMaps": [
    " CIDR4_LMAP_NAME",
    " CIDR4_HMAP_NAME"
  ],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "map_lookup_elem"
  ],
  "compatibleHookpoints": [
    "lwt_xmit",
    "lwt_out",
    "lwt_seg6local",
    "sk_skb",
    "sched_cls",
    "socket_filter",
    "sk_reuseport",
    "sk_msg",
    "kprobe",
    "xdp",
    "cgroup_skb",
    "raw_tracepoint_writable",
    "lwt_in",
    "perf_event",
    "cgroup_sock",
    "cgroup_sock_addr",
    "raw_tracepoint",
    "flow_dissector",
    "cgroup_sysctl",
    "sock_ops",
    "tracepoint",
    "sched_act",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline int check_v4 (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    void *data_end = ctx_data_end (ctx);\n",
    "    void *data = ctx_data (ctx);\n",
    "    struct iphdr *ipv4_hdr = data + sizeof (struct ethhdr);\n",
    "    struct lpm_v4_key pfx __maybe_unused;\n",
    "    if (ctx_no_room (ipv4_hdr + 1, data_end))\n",
    "        return CTX_ACT_DROP;\n",
    "\n",
    "#ifdef CIDR4_FILTER\n",
    "    memcpy (pfx.lpm.data, &ipv4_hdr->saddr, sizeof (pfx.addr));\n",
    "    pfx.lpm.prefixlen = 32;\n",
    "\n",
    "#ifdef CIDR4_LPM_PREFILTER\n",
    "    if (map_lookup_elem (&CIDR4_LMAP_NAME, &pfx))\n",
    "        return CTX_ACT_DROP;\n",
    "\n",
    "#endif /* CIDR4_LPM_PREFILTER */\n",
    "    return map_lookup_elem (&CIDR4_HMAP_NAME, &pfx) ? CTX_ACT_DROP : check_v4_lb (ctx);\n",
    "\n",
    "#else\n",
    "    return check_v4_lb (ctx);\n",
    "\n",
    "#endif /* CIDR4_FILTER */\n",
    "}\n"
  ],
  "called_function_list": [
    "memcpy",
    "check_v4_lb",
    "ctx_data",
    "ctx_data_end",
    "ctx_no_room"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_v4(struct __ctx_buff *ctx)
{
	void *data_end = ctx_data_end(ctx);
	void *data = ctx_data(ctx);
	struct iphdr *ipv4_hdr = data + sizeof(struct ethhdr);
	struct lpm_v4_key pfx __maybe_unused;

	if (ctx_no_room(ipv4_hdr + 1, data_end))
		return CTX_ACT_DROP;

#ifdef CIDR4_FILTER
	memcpy(pfx.lpm.data, &ipv4_hdr->saddr, sizeof(pfx.addr));
	pfx.lpm.prefixlen = 32;

#ifdef CIDR4_LPM_PREFILTER
	if (map_lookup_elem(&CIDR4_LMAP_NAME, &pfx))
		return CTX_ACT_DROP;
#endif /* CIDR4_LPM_PREFILTER */
	return map_lookup_elem(&CIDR4_HMAP_NAME, &pfx) ?
		CTX_ACT_DROP : check_v4_lb(ctx);
#else
	return check_v4_lb(ctx);
#endif /* CIDR4_FILTER */
}
#else
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 181,
  "endLine": 184,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_v4",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlineint",
  "helper": [],
  "compatibleHookpoints": [
    "lwt_xmit",
    "lwt_out",
    "lwt_seg6local",
    "sk_skb",
    "sched_cls",
    "socket_filter",
    "sk_reuseport",
    "sk_msg",
    "kprobe",
    "xdp",
    "cgroup_skb",
    "raw_tracepoint_writable",
    "lwt_in",
    "perf_event",
    "cgroup_sock",
    "cgroup_sock_addr",
    "raw_tracepoint",
    "flow_dissector",
    "cgroup_sysctl",
    "sock_ops",
    "tracepoint",
    "sched_act",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline int check_v4 (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    return check_v4_lb (ctx);\n",
    "}\n"
  ],
  "called_function_list": [
    "memcpy",
    "check_v4_lb",
    "ctx_data",
    "ctx_data_end",
    "ctx_no_room"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_v4(struct __ctx_buff *ctx)
{
	return check_v4_lb(ctx);
}
#endif /* ENABLE_PREFILTER */
#endif /* ENABLE_IPV4 */

#ifdef ENABLE_IPV6
#ifdef ENABLE_NODEPORT_ACCELERATION
__section_tail(CILIUM_MAP_CALLS, CILIUM_CALL_IPV6_FROM_NETDEV)
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 191,
  "endLine": 203,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "tail_lb_ipv6",
  "developer_inline_comments": [
    {
      "start_line": 186,
      "end_line": 186,
      "text": "/* ENABLE_IPV4 */"
    }
  ],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "int",
  "helper": [
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "xdp",
    "sched_act",
    "sched_cls"
  ],
  "source": [
    "int tail_lb_ipv6 (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    int ret = CTX_ACT_OK;\n",
    "    if (!bpf_skip_nodeport (ctx)) {\n",
    "        ret = nodeport_lb6 (ctx, 0);\n",
    "        if (IS_ERR (ret))\n",
    "            return send_drop_notify_error (ctx, 0, ret, CTX_ACT_DROP, METRIC_INGRESS);\n",
    "    }\n",
    "    return bpf_xdp_exit (ctx, ret);\n",
    "}\n"
  ],
  "called_function_list": [
    "IS_ERR",
    "nodeport_lb6",
    "bpf_skip_nodeport",
    "send_drop_notify_error",
    "bpf_xdp_exit"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
int tail_lb_ipv6(struct __ctx_buff *ctx)
{
	int ret = CTX_ACT_OK;

	if (!bpf_skip_nodeport(ctx)) {
		ret = nodeport_lb6(ctx, 0);
		if (IS_ERR(ret))
			return send_drop_notify_error(ctx, 0, ret, CTX_ACT_DROP,
						      METRIC_INGRESS);
	}

	return bpf_xdp_exit(ctx, ret);
}

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 205,
  "endLine": 210,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_v6_lb",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlineint",
  "helper": [],
  "compatibleHookpoints": [
    "lwt_xmit",
    "lwt_out",
    "lwt_seg6local",
    "sk_skb",
    "sched_cls",
    "socket_filter",
    "sk_reuseport",
    "sk_msg",
    "kprobe",
    "xdp",
    "cgroup_skb",
    "raw_tracepoint_writable",
    "lwt_in",
    "perf_event",
    "cgroup_sock",
    "cgroup_sock_addr",
    "raw_tracepoint",
    "flow_dissector",
    "cgroup_sysctl",
    "sock_ops",
    "tracepoint",
    "sched_act",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline int check_v6_lb (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    ep_tail_call (ctx, CILIUM_CALL_IPV6_FROM_NETDEV);\n",
    "    return send_drop_notify_error (ctx, 0, DROP_MISSED_TAIL_CALL, CTX_ACT_DROP, METRIC_INGRESS);\n",
    "}\n"
  ],
  "called_function_list": [
    "send_drop_notify_error",
    "ep_tail_call"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_v6_lb(struct __ctx_buff *ctx)
{
	ep_tail_call(ctx, CILIUM_CALL_IPV6_FROM_NETDEV);
	return send_drop_notify_error(ctx, 0, DROP_MISSED_TAIL_CALL, CTX_ACT_DROP,
				      METRIC_INGRESS);
}
#else
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 212,
  "endLine": 215,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_v6_lb",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff * ctx __maybe_unused"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "xdp",
    "sched_act",
    "sched_cls"
  ],
  "source": [
    "static __always_inline int check_v6_lb (struct  __ctx_buff * ctx __maybe_unused)\n",
    "{\n",
    "    return CTX_ACT_OK;\n",
    "}\n"
  ],
  "called_function_list": [
    "send_drop_notify_error",
    "ep_tail_call"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_v6_lb(struct __ctx_buff *ctx __maybe_unused)
{
	return CTX_ACT_OK;
}
#endif /* ENABLE_NODEPORT_ACCELERATION */

#ifdef ENABLE_PREFILTER
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "map_read",
      "map_read": [
        {
          "Project": "cilium",
          "Return Type": "void*",
          "Description": "Perform a lookup in <[ map ]>(IP: 0) for an entry associated to key. ",
          "Return": " Map value associated to key, or NULL if no entry was found.",
          "Function Name": "map_lookup_elem",
          "Input Params": [
            "{Type: struct map ,Var: *map}",
            "{Type:  const void ,Var: *key}"
          ],
          "compatible_hookpoints": [
            "socket_filter",
            "kprobe",
            "sched_cls",
            "sched_act",
            "tracepoint",
            "xdp",
            "perf_event",
            "cgroup_skb",
            "cgroup_sock",
            "lwt_in",
            "lwt_out",
            "lwt_xmit",
            "sock_ops",
            "sk_skb",
            "cgroup_device",
            "sk_msg",
            "raw_tracepoint",
            "cgroup_sock_addr",
            "lwt_seg6local",
            "sk_reuseport",
            "flow_dissector",
            "cgroup_sysctl",
            "raw_tracepoint_writable"
          ],
          "capabilities": [
            "map_read"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 219,
  "endLine": 242,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_v6",
  "developer_inline_comments": [
    {
      "start_line": 236,
      "end_line": 236,
      "text": "/* CIDR6_LPM_PREFILTER */"
    },
    {
      "start_line": 241,
      "end_line": 241,
      "text": "/* CIDR6_FILTER */"
    }
  ],
  "updateMaps": [],
  "readMaps": [
    " CIDR6_HMAP_NAME",
    " CIDR6_LMAP_NAME"
  ],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "map_lookup_elem"
  ],
  "compatibleHookpoints": [
    "lwt_xmit",
    "lwt_out",
    "lwt_seg6local",
    "sk_skb",
    "sched_cls",
    "socket_filter",
    "sk_reuseport",
    "sk_msg",
    "kprobe",
    "xdp",
    "cgroup_skb",
    "raw_tracepoint_writable",
    "lwt_in",
    "perf_event",
    "cgroup_sock",
    "cgroup_sock_addr",
    "raw_tracepoint",
    "flow_dissector",
    "cgroup_sysctl",
    "sock_ops",
    "tracepoint",
    "sched_act",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline int check_v6 (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    void *data_end = ctx_data_end (ctx);\n",
    "    void *data = ctx_data (ctx);\n",
    "    struct ipv6hdr *ipv6_hdr = data + sizeof (struct ethhdr);\n",
    "    struct lpm_v6_key pfx __maybe_unused;\n",
    "    if (ctx_no_room (ipv6_hdr + 1, data_end))\n",
    "        return CTX_ACT_DROP;\n",
    "\n",
    "#ifdef CIDR6_FILTER\n",
    "    __bpf_memcpy_builtin (pfx.lpm.data, &ipv6_hdr->saddr, sizeof (pfx.addr));\n",
    "    pfx.lpm.prefixlen = 128;\n",
    "\n",
    "#ifdef CIDR6_LPM_PREFILTER\n",
    "    if (map_lookup_elem (&CIDR6_LMAP_NAME, &pfx))\n",
    "        return CTX_ACT_DROP;\n",
    "\n",
    "#endif /* CIDR6_LPM_PREFILTER */\n",
    "    return map_lookup_elem (&CIDR6_HMAP_NAME, &pfx) ? CTX_ACT_DROP : check_v6_lb (ctx);\n",
    "\n",
    "#else\n",
    "    return check_v6_lb (ctx);\n",
    "\n",
    "#endif /* CIDR6_FILTER */\n",
    "}\n"
  ],
  "called_function_list": [
    "check_v6_lb",
    "ctx_data",
    "ctx_data_end",
    "ctx_no_room",
    "__bpf_memcpy_builtin"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_v6(struct __ctx_buff *ctx)
{
	void *data_end = ctx_data_end(ctx);
	void *data = ctx_data(ctx);
	struct ipv6hdr *ipv6_hdr = data + sizeof(struct ethhdr);
	struct lpm_v6_key pfx __maybe_unused;

	if (ctx_no_room(ipv6_hdr + 1, data_end))
		return CTX_ACT_DROP;

#ifdef CIDR6_FILTER
	__bpf_memcpy_builtin(pfx.lpm.data, &ipv6_hdr->saddr, sizeof(pfx.addr));
	pfx.lpm.prefixlen = 128;

#ifdef CIDR6_LPM_PREFILTER
	if (map_lookup_elem(&CIDR6_LMAP_NAME, &pfx))
		return CTX_ACT_DROP;
#endif /* CIDR6_LPM_PREFILTER */
	return map_lookup_elem(&CIDR6_HMAP_NAME, &pfx) ?
		CTX_ACT_DROP : check_v6_lb(ctx);
#else
	return check_v6_lb(ctx);
#endif /* CIDR6_FILTER */
}
#else
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 244,
  "endLine": 247,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_v6",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlineint",
  "helper": [],
  "compatibleHookpoints": [
    "lwt_xmit",
    "lwt_out",
    "lwt_seg6local",
    "sk_skb",
    "sched_cls",
    "socket_filter",
    "sk_reuseport",
    "sk_msg",
    "kprobe",
    "xdp",
    "cgroup_skb",
    "raw_tracepoint_writable",
    "lwt_in",
    "perf_event",
    "cgroup_sock",
    "cgroup_sock_addr",
    "raw_tracepoint",
    "flow_dissector",
    "cgroup_sysctl",
    "sock_ops",
    "tracepoint",
    "sched_act",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline int check_v6 (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    return check_v6_lb (ctx);\n",
    "}\n"
  ],
  "called_function_list": [
    "check_v6_lb",
    "ctx_data",
    "ctx_data_end",
    "ctx_no_room",
    "__bpf_memcpy_builtin"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_v6(struct __ctx_buff *ctx)
{
	return check_v6_lb(ctx);
}
#endif /* ENABLE_PREFILTER */
#endif /* ENABLE_IPV6 */

/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "pkt_go_to_next_module",
      "pkt_go_to_next_module": [
        {
          "Project": "cilium",
          "Return Type": "int",
          "Input Params": [],
          "Function Name": "TC_ACT_OK",
          "Return": 0,
          "Description": "will terminate the packet processing pipeline and allows the packet to proceed. Pass the skb onwards either to upper layers of the stack on ingress or down to the networking device driver for transmission on egress, respectively. TC_ACT_OK sets skb->tc_index based on the classid the tc BPF program set. The latter is set out of the tc BPF program itself through skb->tc_classid from the BPF context.",
          "compatible_hookpoints": [
            "xdp",
            "sched_cls",
            "sched_act"
          ],
          "capabilities": [
            "pkt_go_to_next_module"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 251,
  "endLine": 278,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "check_filters",
  "developer_inline_comments": [
    {
      "start_line": 249,
      "end_line": 249,
      "text": "/* ENABLE_IPV6 */"
    },
    {
      "start_line": 267,
      "end_line": 267,
      "text": "/* ENABLE_IPV4 */"
    },
    {
      "start_line": 272,
      "end_line": 272,
      "text": "/* ENABLE_IPV6 */"
    }
  ],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "static__always_inlineint",
  "helper": [
    "CTX_ACT_OK"
  ],
  "compatibleHookpoints": [
    "xdp",
    "sched_act",
    "sched_cls"
  ],
  "source": [
    "static __always_inline int check_filters (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    int ret = CTX_ACT_OK;\n",
    "    __u16 proto;\n",
    "    if (!validate_ethertype (ctx, &proto))\n",
    "        return CTX_ACT_OK;\n",
    "    ctx_store_meta (ctx, XFER_MARKER, 0);\n",
    "    bpf_skip_nodeport_clear (ctx);\n",
    "    switch (proto) {\n",
    "\n",
    "#ifdef ENABLE_IPV4\n",
    "    case bpf_htons (ETH_P_IP) :\n",
    "        ret = check_v4 (ctx);\n",
    "        break;\n",
    "\n",
    "#endif /* ENABLE_IPV4 */\n",
    "\n",
    "#ifdef ENABLE_IPV6\n",
    "    case bpf_htons (ETH_P_IPV6) :\n",
    "        ret = check_v6 (ctx);\n",
    "        break;\n",
    "\n",
    "#endif /* ENABLE_IPV6 */\n",
    "    default :\n",
    "        break;\n",
    "    }\n",
    "    return bpf_xdp_exit (ctx, ret);\n",
    "}\n"
  ],
  "called_function_list": [
    "validate_ethertype",
    "check_v4",
    "bpf_xdp_exit",
    "check_v6",
    "ctx_store_meta",
    "bpf_htons",
    "bpf_skip_nodeport_clear"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
static __always_inline int check_filters(struct __ctx_buff *ctx)
{
	int ret = CTX_ACT_OK;
	__u16 proto;

	if (!validate_ethertype(ctx, &proto))
		return CTX_ACT_OK;

	ctx_store_meta(ctx, XFER_MARKER, 0);
	bpf_skip_nodeport_clear(ctx);

	switch (proto) {
#ifdef ENABLE_IPV4
	case bpf_htons(ETH_P_IP):
		ret = check_v4(ctx);
		break;
#endif /* ENABLE_IPV4 */
#ifdef ENABLE_IPV6
	case bpf_htons(ETH_P_IPV6):
		ret = check_v6(ctx);
		break;
#endif /* ENABLE_IPV6 */
	default:
		break;
	}

	return bpf_xdp_exit(ctx, ret);
}

__section("from-netdev")
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 281,
  "endLine": 284,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/bpf_xdp.c",
  "funcName": "bpf_xdp_entry",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "struct  __ctx_buff *ctx"
  ],
  "output": "int",
  "helper": [],
  "compatibleHookpoints": [
    "lwt_xmit",
    "lwt_out",
    "lwt_seg6local",
    "sk_skb",
    "sched_cls",
    "socket_filter",
    "sk_reuseport",
    "sk_msg",
    "kprobe",
    "xdp",
    "cgroup_skb",
    "raw_tracepoint_writable",
    "lwt_in",
    "perf_event",
    "cgroup_sock",
    "cgroup_sock_addr",
    "raw_tracepoint",
    "flow_dissector",
    "cgroup_sysctl",
    "sock_ops",
    "tracepoint",
    "sched_act",
    "cgroup_device"
  ],
  "source": [
    "int bpf_xdp_entry (struct  __ctx_buff *ctx)\n",
    "{\n",
    "    return check_filters (ctx);\n",
    "}\n"
  ],
  "called_function_list": [
    "check_filters"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
int bpf_xdp_entry(struct __ctx_buff *ctx)
{
	return check_filters(ctx);
}

BPF_LICENSE("Dual BSD/GPL");