/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/SrcPackage.cc
 *
*/
#include "zypp/SrcPackage.h"
#include "zypp/source/SourceImpl.h"
#include "zypp/base/Exception.h"

using namespace std;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////

  IMPL_PTR_TYPE(SrcPackage);

  ///////////////////////////////////////////////////////////////////
  //
  //	METHOD NAME : SrcPackage::SrcPackage
  //	METHOD TYPE : Ctor
  //
  SrcPackage::SrcPackage( const NVRAD & nvrad_r )
  : ResObject( TraitsType::kind, nvrad_r )
  {}

  ///////////////////////////////////////////////////////////////////
  //
  //	METHOD NAME : SrcPackage::~SrcPackage
  //	METHOD TYPE : Dtor
  //
  SrcPackage::~SrcPackage()
  {}

  ///////////////////////////////////////////////////////////////////
  //
  //	SrcPackage interface forwarded to implementation
  //
  ///////////////////////////////////////////////////////////////////

  ByteCount SrcPackage::archivesize() const
  { return pimpl().archivesize(); }

  DiskUsage SrcPackage::diskusage() const
  { return pimpl().diskusage(); }

  Pathname SrcPackage::location() const
  { return pimpl().location(); }

  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
