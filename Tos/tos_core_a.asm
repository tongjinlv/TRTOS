
    INCLUDE tos_core_a.h


    ;��ջ8�ֽڶ���
    PRESERVE8

    AREA    TOS_CORE_A, CODE, READONLY
    THUMB


    ;��������: ʵ�������л�����, ���Ĵ������ݵ���ǰ�����ջ��, �ӽ�Ҫ���������ջ��
    ;          ȡ���Ĵ�������ֵ����ת����Ҫ��������ִ��.
    ;��ڲ���: none.
    ;�� �� ֵ: none.
TOS_ContextSwitch

    ;���浱ǰ����Ķ�ջ��Ϣ
    SUB    R13, #0x8;��ջָ����
    PUSH   {R0 - R12}
    MRS    R0, XPSR;�������⹦�ܼĴ���
    PUSH   {R0};ѹ�����⹦�ܼĴ�����ֵ
    MOV    R0, R13;
    ADD    R0, #0x40
    STMDB  R0, {R0, R14};��ͬ��PUSH

    ;���浱ǰ�����ָ��ֵ
    LDR    R0, =gpuiCurTaskSpAddr
    LDR    R1, [R0]
    STR    R13, [R1]

    ;��ȡ��Ҫ���������ָ��
    LDR    R0, =guiNextTaskSp
    LDR    R13, [R0]

    ;��ȡ��Ҫ��������Ķ�ջ��Ϣ������������
    POP    {R0}
    MSR    XPSR, R0
    POP    {R0 - R12}
    ADD    R13, #4
	
    POP    {PC}

    ;��������: ʵ�ִ��޲���ϵͳ״̬�л�������ϵͳ״̬, ��Root�����ջ��ȡ���Ĵ�����
    ;          ��ֵ����ת��Root����ִ��.
    ;��ڲ���: none.
    ;�� �� ֵ: none.
TOS_SwitchToTask

    ;��ȡ��Ҫ���������ָ��
    LDR    R0, =guiNextTaskSp;
    LDR    R13, [R0];��ת

    ;��ȡ��Ҫ��������Ķ�ջ��Ϣ������������
    POP    {R0}
    MSR    XPSR, R0;�洢ͨ�üĴ�����ֵ����Ĵ�����MODE_USR
    POP    {R0 - R12};�ָ��Ĵ�����ֵ�Ӷ�ջ
    ADD    R13, #4;����pstrTcb
    POP    {PC}  ;ֱ������vfFuncPointer

    ALIGN
    END

