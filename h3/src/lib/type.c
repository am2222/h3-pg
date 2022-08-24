/*
 * Copyright 2018-2022 Bytes & Brains
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <postgres.h>		 // Datum, etc.
#include <fmgr.h>			 // PG_FUNCTION_ARGS, etc.

#include <h3api.h> // Main H3 include
#include "extension.h"

/* conversion */
PG_FUNCTION_INFO_V1(h3index_in);
PG_FUNCTION_INFO_V1(h3index_out);
PG_FUNCTION_INFO_V1(h3index_to_bigint);
PG_FUNCTION_INFO_V1(bigint_to_h3index);

/* textual input/output functions */
Datum
h3index_in(PG_FUNCTION_ARGS)
{
	H3Error		error;
	H3Index		h3;
	char	   *string = PG_GETARG_CSTRING(0);

	error = stringToH3(string, &h3);
	H3_ERROR(error, "stringToH3");

	PG_RETURN_H3INDEX(h3);
}

Datum
h3index_out(PG_FUNCTION_ARGS)
{
	H3Error		error;
	H3Index		h3 = PG_GETARG_H3INDEX(0);
	char	   *string = palloc(17 * sizeof(char));

	error = h3ToString(h3, string, 17);
	H3_ERROR(error, "h3ToString");

	PG_RETURN_CSTRING(string);
}

/* bigint conversion functions */
Datum
h3index_to_bigint(PG_FUNCTION_ARGS)
{
	H3Index		h3index = PG_GETARG_H3INDEX(0);

	PG_RETURN_INT64(h3index);
}

Datum
bigint_to_h3index(PG_FUNCTION_ARGS)
{
	int64_t		bigint = PG_GETARG_INT64(0);

	PG_RETURN_H3INDEX(bigint);
}
