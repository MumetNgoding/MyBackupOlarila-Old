/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20180427 (64-bit version)(RM)
 * Copyright (c) 2000 - 2018 Intel Corporation
 * 
 * Disassembling to non-symbolic legacy ASL operators
 *
 * Disassembly of SSDT-1.aml, Thu Dec 12 15:30:02 2019
 *
 * Original Table Header:
 *     Signature        "SSDT"
 *     Length           0x0000049E (1182)
 *     Revision         0x01
 *     Checksum         0xE7
 *     OEM ID           "AhciR2"
 *     OEM Table ID     "AhciTab2"
 *     OEM Revision     0x00001000 (4096)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20091112 (537465106)
 */
DefinitionBlock ("", "SSDT", 1, "AhciR2", "AhciTab2", 0x00001000)
{
    /*
     * External declarations were imported from
     * a reference file -- DSDT.aml
     */

    External (_SB_.HDDF, UnknownObj)    // Warning: Unknown object
    External (_SB_.PCI0.IDE1, DeviceObj)    // Warning: Unknown object

    Scope (\_SB.PCI0.IDE1)
    {
        Name (REGF, One)
        Method (_REG, 2, NotSerialized)  // _REG: Region Availability
        {
            If (LEqual (Arg0, 0x02))
            {
                Store (Arg1, REGF)
            }
        }

        OperationRegion (BAR0, PCI_Config, Zero, 0x0100)
        Field (BAR0, DWordAcc, NoLock, Preserve)
        {
            VDID,   32, 
            Offset (0x0A), 
            SCCR,   8, 
            BCCR,   8, 
            Offset (0x90), 
            MAPV,   2, 
                ,   4, 
            SMS,    2, 
            Offset (0x92), 
            P0EN,   1, 
            P1EN,   1, 
            P2EN,   1, 
            P3EN,   1, 
            P4EN,   1, 
            P5EN,   1, 
                ,   1, 
            Offset (0x93), 
            P0PF,   1, 
            P1PF,   1, 
            P2PF,   1, 
            P3PF,   1, 
            P4PF,   1, 
            P5PF,   1, 
                ,   1, 
            Offset (0x94)
        }

        Name (AT01, Buffer (0x07)
        {
             0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF       
        })
        Name (AT02, Buffer (0x07)
        {
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90       
        })
        Name (AT03, Buffer (0x07)
        {
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6       
        })
        Name (AT04, Buffer (0x07)
        {
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91       
        })
        Name (AT05, Buffer (0x07)
        {
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF5       
        })
        Name (AT06, Buffer (0x07)
        {
             0x10, 0x03, 0x00, 0x00, 0x00, 0x00, 0xEF       
        })
        Name (AT07, Buffer (0x07)
        {
             0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0xEF       
        })
        Name (AT08, Buffer (0x07)
        {
             0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF       
        })
        Name (AT81, Buffer (0x07)
        {
             0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF       
        })
        Name (AT09, Buffer (0x07)
        {
             0x90, 0x05, 0x00, 0x00, 0x00, 0x00, 0xEF       
        })
        Name (ATA0, Buffer (0x32){})
        Name (ATA1, Buffer (0x32){})
        Name (ATA2, Buffer (0x32){})
        Name (ATA3, Buffer (0x32){})
        Name (ATAB, Buffer (0x32){})
        CreateByteField (ATAB, Zero, CMDC)
        Method (GTFB, 3, Serialized)
        {
            Multiply (CMDC, 0x38, Local0)
            Add (Local0, 0x08, Local1)
            CreateField (ATAB, Local1, 0x38, CMDX)
            Multiply (CMDC, 0x07, Local0)
            CreateByteField (ATAB, Add (Local0, 0x02), A001)
            CreateByteField (ATAB, Add (Local0, 0x06), A005)
            Store (Arg0, CMDX)
            Store (Arg1, A001)
            Store (Arg2, A005)
            Increment (CMDC)
        }

        Method (GTF, 2, Serialized)
        {
            Store (Arg1, Debug)
            Store (Zero, CMDC)
            Name (ID00, Zero)
            Name (ID49, 0x0C00)
            Name (ID59, Zero)
            Name (ID53, 0x04)
            Name (ID63, 0x0F00)
            Name (ID88, 0x0F00)
            Name (ID78, Zero)
            Name (W128, Zero)
            Name (W119, Zero)
            Name (W120, Zero)
            Name (IRDY, One)
            Name (PIOT, Zero)
            Name (DMAT, Zero)
            If (LEqual (SizeOf (Arg1), 0x0200))
            {
                CreateWordField (Arg1, Zero, IW00)
                Store (IW00, ID00)
                CreateWordField (Arg1, 0x62, IW49)
                Store (IW49, ID49)
                CreateWordField (Arg1, 0x6A, IW53)
                Store (IW53, ID53)
                CreateWordField (Arg1, 0x7E, IW63)
                Store (IW63, ID63)
                CreateWordField (Arg1, 0x76, IW59)
                Store (IW59, ID59)
                CreateWordField (Arg1, 0xB0, IW88)
                Store (IW88, ID88)
                CreateWordField (Arg1, 0x9C, IW78)
                Store (IW78, ID78)
                CreateWordField (Arg1, 0x0100, I128)
                Store (I128, W128)
                CreateWordField (Arg1, 0xEE, I119)
                Store (I119, W119)
                CreateWordField (Arg1, 0xF0, I120)
                Store (I120, W120)
            }

            Store (0xA0, Local7)
            If (Arg0)
            {
                Store (0xB0, Local7)
            }

            If (LAnd (And (ID59, 0x0100), And (ID59, 0xFF)))
            {
                GTFB (AT03, And (ID59, 0xFF), Local7)
            }

            If (LEqual (Local7, 0xA0))
            {
                If (And (W128, One))
                {
                    GTFB (AT05, Zero, Local7)
                }

                If (And (ID78, 0x40))
                {
                    GTFB (AT07, 0x06, Local7)
                }

                If (And (ID78, 0x08))
                {
                    GTFB (AT06, 0x03, Local7)
                }

                If (And (W119, 0x20))
                {
                    If (And (\_SB.HDDF, One))
                    {
                        GTFB (AT08, Zero, Local7)
                    }
                    Else
                    {
                        GTFB (AT81, Zero, Local7)
                    }
                }
            }

            Store (ATAB, Debug)
            Return (ATAB)
        }

        Method (RATA, 1, NotSerialized)
        {
            CreateByteField (Arg0, Zero, CMDN)
            Multiply (CMDN, 0x38, Local0)
            CreateField (Arg0, 0x08, Local0, RETB)
            Store (RETB, Debug)
            Return (RETB)
        }

        Method (AGTF, 2, Serialized)
        {
            Store (0xA0, Local0)
            Store (Zero, CMDC)
            If (LEqual (SizeOf (Arg1), 0x0200))
            {
                CreateWordField (Arg1, Zero, IW00)
                CreateWordField (Arg1, 0x0100, I128)
                If (And (I128, One))
                {
                    GTFB (AT05, Zero, Local0)
                }

                CreateWordField (Arg1, 0x9C, IW78)
                If (And (IW78, 0x40))
                {
                    GTFB (AT07, 0x06, Local0)
                }

                If (And (IW78, 0x08))
                {
                    GTFB (AT06, 0x03, Local0)
                }

                CreateWordField (Arg1, 0xEE, I119)
                If (And (I119, 0x20))
                {
                    If (And (\_SB.HDDF, One))
                    {
                        GTFB (AT08, Zero, Local0)
                    }
                    Else
                    {
                        GTFB (AT81, Zero, Local0)
                    }
                }
            }

            Return (ATAB)
        }
    }
}

