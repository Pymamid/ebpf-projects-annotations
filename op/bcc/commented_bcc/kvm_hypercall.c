#define EXIT_REASON 18
BPF_HASH(start, u8, u8);
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 3,
  "endLine": 11,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/bcc/kvm_hypercall.c",
  "funcName": "TRACEPOINT_PROBE",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "kvm",
    " kvm_exit"
  ],
  "output": "NA",
  "helper": [
    "bpf_trace_printk"
  ],
  "compatibleHookpoints": [
    "sk_skb",
    "raw_tracepoint",
    "cgroup_sock",
    "sock_ops",
    "cgroup_sysctl",
    "lwt_out",
    "sched_cls",
    "kprobe",
    "cgroup_sock_addr",
    "sk_reuseport",
    "cgroup_skb",
    "perf_event",
    "cgroup_device",
    "lwt_seg6local",
    "flow_dissector",
    "socket_filter",
    "lwt_in",
    "xdp",
    "sched_act",
    "lwt_xmit",
    "tracepoint",
    "raw_tracepoint_writable",
    "sk_msg"
  ],
  "source": [
    "TRACEPOINT_PROBE (kvm, kvm_exit)\n",
    "{\n",
    "    u8 e = EXIT_REASON;\n",
    "    u8 one = 1;\n",
    "    if (args->exit_reason == EXIT_REASON) {\n",
    "        bpf_trace_printk (\"KVM_EXIT exit_reason : %d\\\\n\", args->exit_reason);\n",
    "        start.update (&e, &one);\n",
    "    }\n",
    "    return 0;\n",
    "}\n"
  ],
  "called_function_list": [
    "lookup",
    "update"
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
TRACEPOINT_PROBE(kvm, kvm_exit) {
	u8 e = EXIT_REASON;
	u8 one = 1;
	if (args->exit_reason == EXIT_REASON) {
		bpf_trace_printk("KVM_EXIT exit_reason : %d\\n", args->exit_reason);
		start.update(&e, &one);
	}
	return 0;
}
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 12,
  "endLine": 21,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/bcc/kvm_hypercall.c",
  "funcName": "TRACEPOINT_PROBE",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "kvm",
    " kvm_entry"
  ],
  "output": "NA",
  "helper": [
    "bpf_trace_printk"
  ],
  "compatibleHookpoints": [
    "sk_skb",
    "raw_tracepoint",
    "cgroup_sock",
    "sock_ops",
    "cgroup_sysctl",
    "lwt_out",
    "sched_cls",
    "kprobe",
    "cgroup_sock_addr",
    "sk_reuseport",
    "cgroup_skb",
    "perf_event",
    "cgroup_device",
    "lwt_seg6local",
    "flow_dissector",
    "socket_filter",
    "lwt_in",
    "xdp",
    "sched_act",
    "lwt_xmit",
    "tracepoint",
    "raw_tracepoint_writable",
    "sk_msg"
  ],
  "source": [
    "TRACEPOINT_PROBE (kvm, kvm_entry)\n",
    "{\n",
    "    u8 e = EXIT_REASON;\n",
    "    u8 zero = 0;\n",
    "    u8 *s = start.lookup (&e);\n",
    "    if (s != NULL && *s == 1) {\n",
    "        bpf_trace_printk (\"KVM_ENTRY vcpu_id : %u\\\\n\", args->vcpu_id);\n",
    "        start.update (&e, &zero);\n",
    "    }\n",
    "    return 0;\n",
    "}\n"
  ],
  "called_function_list": [
    "lookup",
    "update"
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
TRACEPOINT_PROBE(kvm, kvm_entry) {
	u8 e = EXIT_REASON;
	u8 zero = 0;
	u8 *s = start.lookup(&e);
	if (s != NULL && *s == 1) {
		bpf_trace_printk("KVM_ENTRY vcpu_id : %u\\n", args->vcpu_id);
		start.update(&e, &zero);
	}
	return 0;
}
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 22,
  "endLine": 30,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/bcc/kvm_hypercall.c",
  "funcName": "TRACEPOINT_PROBE",
  "developer_inline_comments": [],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "kvm",
    " kvm_hypercall"
  ],
  "output": "NA",
  "helper": [
    "bpf_trace_printk"
  ],
  "compatibleHookpoints": [
    "sk_skb",
    "raw_tracepoint",
    "cgroup_sock",
    "sock_ops",
    "cgroup_sysctl",
    "lwt_out",
    "sched_cls",
    "kprobe",
    "cgroup_sock_addr",
    "sk_reuseport",
    "cgroup_skb",
    "perf_event",
    "cgroup_device",
    "lwt_seg6local",
    "flow_dissector",
    "socket_filter",
    "lwt_in",
    "xdp",
    "sched_act",
    "lwt_xmit",
    "tracepoint",
    "raw_tracepoint_writable",
    "sk_msg"
  ],
  "source": [
    "TRACEPOINT_PROBE (kvm, kvm_hypercall)\n",
    "{\n",
    "    u8 e = EXIT_REASON;\n",
    "    u8 zero = 0;\n",
    "    u8 *s = start.lookup (&e);\n",
    "    if (s != NULL && *s == 1) {\n",
    "        bpf_trace_printk (\"HYPERCALL nr : %d\\\\n\", args->nr);\n",
    "    }\n",
    "    return 0;\n",
    "}\n"
  ],
  "called_function_list": [
    "lookup",
    "update"
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
TRACEPOINT_PROBE(kvm, kvm_hypercall) {
	u8 e = EXIT_REASON;
	u8 zero = 0;
	u8 *s = start.lookup(&e);
	if (s != NULL && *s == 1) {
		bpf_trace_printk("HYPERCALL nr : %d\\n", args->nr);
	}
	return 0;
};