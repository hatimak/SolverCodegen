set moduleName RLC_Circuit_solverCore
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 1
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {RLC_Circuit_solverCore}
set C_modelType { void 0 }
set C_modelArgList {
	{ x_out_0_V int 64 regular {pointer 1}  }
	{ x_out_1_V int 64 regular {pointer 1}  }
	{ l_current_ind_V int 64 regular {pointer 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "x_out_0_V", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "x_out.V","cData": "int64","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 0,"up" : 0,"step" : 2}]}]}]} , 
 	{ "Name" : "x_out_1_V", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "x_out.V","cData": "int64","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 1,"up" : 1,"step" : 2}]}]}]} , 
 	{ "Name" : "l_current_ind_V", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "l_current_ind.V","cData": "int64","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} ]}
# RTL Port declarations: 
set portNum 12
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ x_out_0_V sc_out sc_lv 64 signal 0 } 
	{ x_out_0_V_ap_vld sc_out sc_logic 1 outvld 0 } 
	{ x_out_1_V sc_out sc_lv 64 signal 1 } 
	{ x_out_1_V_ap_vld sc_out sc_logic 1 outvld 1 } 
	{ l_current_ind_V sc_out sc_lv 64 signal 2 } 
	{ l_current_ind_V_ap_vld sc_out sc_logic 1 outvld 2 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "x_out_0_V", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "x_out_0_V", "role": "default" }} , 
 	{ "name": "x_out_0_V_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "x_out_0_V", "role": "ap_vld" }} , 
 	{ "name": "x_out_1_V", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "x_out_1_V", "role": "default" }} , 
 	{ "name": "x_out_1_V_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "x_out_1_V", "role": "ap_vld" }} , 
 	{ "name": "l_current_ind_V", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "l_current_ind_V", "role": "default" }} , 
 	{ "name": "l_current_ind_V_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "l_current_ind_V", "role": "ap_vld" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "",
		"CDFG" : "RLC_Circuit_solverCore",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "x_out_0_V", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "x_out_1_V", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "l_current_ind_V", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "x_V_1", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "x_V_2", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "current_eq_ind_V", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "current_eq_cap_V", "Type" : "OVld", "Direction" : "IO"}]}]}


set ArgLastReadFirstWriteLatency {
	RLC_Circuit_solverCore {
		x_out_0_V {Type O LastRead -1 FirstWrite 0}
		x_out_1_V {Type O LastRead -1 FirstWrite 0}
		l_current_ind_V {Type O LastRead -1 FirstWrite 0}
		x_V_1 {Type IO LastRead -1 FirstWrite -1}
		x_V_2 {Type IO LastRead -1 FirstWrite -1}
		current_eq_ind_V {Type IO LastRead -1 FirstWrite -1}
		current_eq_cap_V {Type IO LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "0", "Max" : "0"}
	, {"Name" : "Interval", "Min" : "1", "Max" : "1"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	x_out_0_V { ap_vld {  { x_out_0_V out_data 1 64 }  { x_out_0_V_ap_vld out_vld 1 1 } } }
	x_out_1_V { ap_vld {  { x_out_1_V out_data 1 64 }  { x_out_1_V_ap_vld out_vld 1 1 } } }
	l_current_ind_V { ap_vld {  { l_current_ind_V out_data 1 64 }  { l_current_ind_V_ap_vld out_vld 1 1 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
