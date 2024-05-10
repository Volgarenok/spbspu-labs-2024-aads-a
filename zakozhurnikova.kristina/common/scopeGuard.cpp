#include "scopeGuard.hpp"

zakozhurnikova::ScopeGuard::ScopeGuard(std::basic_ios< char >& stream):
  stream_(stream),
  flags_(stream.flags())
{}

zakozhurnikova::ScopeGuard::~ScopeGuard()
{
  stream_.flags(flags_);
}
