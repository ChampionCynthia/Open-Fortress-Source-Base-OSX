# My notes
Cleaning up warnings would be nice.

Running a Mac build would also be nice, but takes a bit of time.

I should set up a way of building Windows binaries.

## Future Issues
Not written yet, as I'm troubleshooting something else.
### We're missing some kind of chat feature
This one probably isn't an issue.
```
CUserMessages::HookMessage:  no such message SayText2
usermessages.cpp (129) : Assertion Failed: 0
ASSERT: /of/src/src/game/client/../../game/shared/usermessages.cpp:129:Assertion Failed: 0
```
### We have no weapon selection
```
clientmode_shared.cpp (336) : Assertion Failed: m_pWeaponSelection
ASSERT: /of/src/src/game/client/clientmode_shared.cpp:336:Assertion Failed: m_pWeaponSelection
	m_pWeaponSelection = ( CBaseHudWeaponSelection * )GET_HUDELEMENT( CHudWeaponSelection );
	Assert( m_pWeaponSelection );
```

### We have no crosshair?
or don't support tf2's
```
Could not find Hud Element: CHudCrosshair
hud.cpp (909) : Assertion Failed: 0
ASSERT: /of/src/src/game/client/hud.cpp:909:Assertion Failed: 0
```

### We don't support some TF2 anim script thing
Could be modification done by 'em to the baseviewport after releasing SSDK
```
Couldn't parse script sequence 'QuestItem_Identify_Expand': expected <anim command>, found '0.4'
baseviewport.cpp (151) : Assertion Failed: 0
ASSERT: /of/src/src/game/client/game_controls/baseviewport.cpp:151:Assertion Failed: 0
```

### particles.a misuses utlbuffer.cpp
Either disable the assertion, fix the particle scripts, patch particles.a, or disable the assertion iff we're being called by particles.a.
```
utlbuffer.cpp (618) : Assertion Failed: maxLenInChars != 0
ASSERT: /of/src/src/tier1/utlbuffer.cpp:618:Assertion Failed: maxLenInChars != 0
  libtier0.so(DoNewAssertDialog+0x1d8) [0xf7948b88]
  client.so(+0x7d8595) [0xe2b49595]
  client.so(+0x7d8b7a) [0xe2b49b7a]
  client.so(+0x9ad665) [0xe2d1e665]
  client.so(+0x99fc76) [0xe2d10c76]
  client.so(+0x88100f) [0xe2bf200f]
  client.so(+0x8815b9) [0xe2bf25b9]
  client.so(+0x881b07) [0xe2bf2b07]
  client.so(+0x881cbd) [0xe2bf2cbd]
  client.so(+0x375f5c) [0xe26e6f5c]
  client.so(+0x709af8) [0xe2a7aaf8]
  client.so(+0x4796eb) [0xe27ea6eb]
  engine.so(+0x387976) [0xe819d976]
  engine.so(+0x4787b0) [0xe828e7b0]
  engine.so(+0x572718) [0xe8388718]
  engine.so(+0x577a6f) [0xe838da6f]

Thread 1 "hl2_linux" received signal SIGTRAP, Trace/breakpoint trap.
0xf7fd1569 in __kernel_vsyscall ()
(gdb) bt
#0  0xf7fd1569 in __kernel_vsyscall ()
#1  0xf7f4dc39 in __libc_signal_restore_set (set=0xffffc45c) at ../sysdeps/unix/sysv/linux/internal-signals.h:84
#2  raise (sig=5) at ../sysdeps/unix/sysv/linux/raise.c:48
#3  0xe2b495b5 in CUtlBuffer::GetStringInternal (this=0xffffc750, pString=0x117000a0 "", maxLenInChars=0) at /of/src/src/tier1/utlbuffer.cpp:618
#4  0xe2b49b7a in CUtlBuffer::GetDelimitedString (this=0xffffc750, pConv=0x0, pString=0x117000a0 "", nMaxChars=0) at /of/src/src/tier1/utlbuffer.cpp:733
#5  0xe2d1e665 in Unserialize (buf=..., dest=...) at /of/src/src/tier1/utlbufferutil.cpp:554
#6  0xe2d10c76 in CDmxElement::UnpackIntoStructure (this=0x1794a040, pData=0x1108b100, DestSizeInBytes=836,
    pUnpack=0xe3078000 <DmxElementUnpackInit<CParticleSystemDefinition>(CParticleSystemDefinition*)::unpack+192>)
    at /home/johns/valve/ValveGames/rel/hl2/src/dmxloader/dmxelement.cpp:379
#7  0xe2bf200f in CParticleSystemDefinition::Read (this=0x1108b100, pElement=0x1794a040) at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:559
#8  0xe2bf25b9 in CParticleSystemDictionary::AddParticleSystem (this=0x10f062a0, pParticleSystem=0x1794a040)
    at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:228
#9  0xe2bf2b07 in CParticleSystemMgr::ReadParticleDefinitions (this=0xe30e7700 <s_ParticleSystemMgr>, buf=..., pFileName=0x172b3c41 "particles/error.pcf",
    bPrecache=true, bDecommitTempMemory=false) at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:3168
#10 0xe2bf2cbd in CParticleSystemMgr::ReadParticleConfigFile (pFileName=0x172b3c41 "particles/error.pcf", bDecommitTempMemory=false, bPrecache=<optimized out>,
    buf=..., this=0xe30e7700 <s_ParticleSystemMgr>) at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:3284
#11 CParticleSystemMgr::ReadParticleConfigFile (this=0xe30e7700 <s_ParticleSystemMgr>, pFileName=0x172b3c41 "particles/error.pcf", bPrecache=<optimized out>,
    bDecommitTempMemory=false) at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:3359
#12 0xe26e6f5c in ParseParticleEffects (bLoadSheets=true, bPrecache=false) at /of/src/src/game/client/../../game/shared/particle_parse.cpp:107
#13 0xe2a7aaf8 in CParticleMgr::Init (this=0xe30cb8c0 <ParticleMgr()::s_ParticleMgr>, count=2048, pMaterials=0xe7b33ea0) at /of/src/src/game/client/particlemgr.cpp:1084
#14 0xe27ea6eb in CHLClient::Init (this=0xe308a704 <gHLClient>, appSystemFactory=0xe83e9530, physicsFactory=0xe83e9530, pGlobals=0xe8973900)
    at /of/src/src/game/client/cdll_client_int.cpp:995
#15 0xe819d976 in ?? () from /home/magnus/.local/share/Steam/steamapps/common/Source SDK Base 2013 Multiplayer/bin/engine.so
#16 0xe828e7b0 in ?? () from /home/magnus/.local/share/Steam/steamapps/common/Source SDK Base 2013 Multiplayer/bin/engine.so
#17 0xe8388718 in ?? () from /home/magnus/.local/share/Steam/steamapps/common/Source SDK Base 2013 Multiplayer/bin/engine.so
#18 0xe838da6f in ?? () from /home/magnus/.local/share/Steam/steamapps/common/Source SDK Base 2013 Multiplayer/bin/engine.so
#19 0xe838a246 in ?? () from /home/magnus/.local/share/Steam/steamapps/common/Source SDK Base 2013 Multiplayer/bin/engine.so
#20 0xe83e9ac0 in ?? () from /home/magnus/.local/share/Steam/steamapps/common/Source SDK Base 2013 Multiplayer/bin/engine.so
#21 0xe838bf1f in ?? () from /home/magnus/.local/share/Steam/steamapps/common/Source SDK Base 2013 Multiplayer/bin/engine.so
#22 0xf7997300 in ?? () from bin/launcher.so
#23 0xf7997300 in ?? () from bin/launcher.so
#24 0xf7978cad in LauncherMain () from bin/launcher.so
#25 0x0804877b in main ()
(gdb)
#0  0xf7fd1569 in __kernel_vsyscall ()
#1  0xf7f4dc39 in __libc_signal_restore_set (set=0xffffc45c) at ../sysdeps/unix/sysv/linux/internal-signals.h:84
#2  raise (sig=5) at ../sysdeps/unix/sysv/linux/raise.c:48
#3  0xe2b495b5 in CUtlBuffer::GetStringInternal (this=0xffffc750, pString=0x117000a0 "", maxLenInChars=0) at /of/src/src/tier1/utlbuffer.cpp:618
#4  0xe2b49b7a in CUtlBuffer::GetDelimitedString (this=0xffffc750, pConv=0x0, pString=0x117000a0 "", nMaxChars=0) at /of/src/src/tier1/utlbuffer.cpp:733
#5  0xe2d1e665 in Unserialize (buf=..., dest=...) at /of/src/src/tier1/utlbufferutil.cpp:554
#6  0xe2d10c76 in CDmxElement::UnpackIntoStructure (this=0x1794a040, pData=0x1108b100, DestSizeInBytes=836,
    pUnpack=0xe3078000 <DmxElementUnpackInit<CParticleSystemDefinition>(CParticleSystemDefinition*)::unpack+192>)
    at /home/johns/valve/ValveGames/rel/hl2/src/dmxloader/dmxelement.cpp:379
#7  0xe2bf200f in CParticleSystemDefinition::Read (this=0x1108b100, pElement=0x1794a040) at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:559
#8  0xe2bf25b9 in CParticleSystemDictionary::AddParticleSystem (this=0x10f062a0, pParticleSystem=0x1794a040)
    at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:228
#9  0xe2bf2b07 in CParticleSystemMgr::ReadParticleDefinitions (this=0xe30e7700 <s_ParticleSystemMgr>, buf=..., pFileName=0x172b3c41 "particles/error.pcf",
    bPrecache=true, bDecommitTempMemory=false) at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:3168
#10 0xe2bf2cbd in CParticleSystemMgr::ReadParticleConfigFile (pFileName=0x172b3c41 "particles/error.pcf", bDecommitTempMemory=false, bPrecache=<optimized out>,
    buf=..., this=0xe30e7700 <s_ParticleSystemMgr>) at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:3284
#11 CParticleSystemMgr::ReadParticleConfigFile (this=0xe30e7700 <s_ParticleSystemMgr>, pFileName=0x172b3c41 "particles/error.pcf", bPrecache=<optimized out>,
    bDecommitTempMemory=false) at /home/johns/valve/ValveGames/rel/hl2/src/particles/particles.cpp:3359
#12 0xe26e6f5c in ParseParticleEffects (bLoadSheets=true, bPrecache=false) at /of/src/src/game/client/../../game/shared/particle_parse.cpp:107
#13 0xe2a7aaf8 in CParticleMgr::Init (this=0xe30cb8c0 <ParticleMgr()::s_ParticleMgr>, count=2048, pMaterials=0xe7b33ea0) at /of/src/src/game/client/particlemgr.cpp:1084
#14 0xe27ea6eb in CHLClient::Init (this=0xe308a704 <gHLClient>, appSystemFactory=0xe83e9530, physicsFactory=0xe83e9530, pGlobals=0xe8973900)
    at /of/src/src/game/client/cdll_client_int.cpp:995
```

## Modified Source Source Header
```
// Open Fortress Modifications (CC-BY-NC-CA)
// * 
```

## New OF Source Header

```
// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: 
// Author(s): Nopey
//
```
