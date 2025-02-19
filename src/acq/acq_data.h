#ifndef ACQ_DATA_H
#define ACQ_DATA_H

#include "acq_enums.h"
#include "common/base_io.h"
#include "common/structs.h"

namespace scpi_rp {

bool getAcqWritePointer(BaseIO *io, uint32_t *position);
bool getAcqTriggerPointer(BaseIO *io, uint32_t *position);

bool getAcqWritePointerCh(BaseIO *io, EACQChannel channel, uint32_t *position);
bool getAcqTriggerPointerCh(BaseIO *io, EACQChannel channel,
                            uint32_t *position);

}  // namespace scpi_rp

#endif
