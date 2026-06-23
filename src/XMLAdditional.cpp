#include "XMLAdditional.h"

StrX::StrX(const XMLCh* const toTranscode)
    {
        // Call the private transcoding method
        fLocalForm = XMLString::transcode(toTranscode);
    }

StrX::~StrX()
    {
        XMLString::release(&fLocalForm);
    }

// -----------------------------------------------------------------------
//  Getter methods
// -----------------------------------------------------------------------

const char* StrX::localForm() const
{
  return fLocalForm;
}


