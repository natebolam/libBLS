/*
Copyright (C) 2018-2019 SKALE Labs

This file is part of libBLS.

libBLS is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libBLS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with libBLS.  If not, see <https://www.gnu.org/licenses/>.

@file utils.cpp
@author Oleh Nikolaiev
@date 2019
*/

#include <threshold_encryption/utils.h>

libff::bigint<num_limbs> modulus = libff::bigint<num_limbs>("8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791");

void MpzSquareRoot(mpz_t ret_val, mpz_t x) {
  libff::bigint<num_limbs> to_find_square_root = libff::bigint<num_limbs>("2195177699915828130609445496188512453951720799853552052757163349816618907720055739269656294855665555355788964692395579364819428341829370331231282499556198"); //type_a_Fq(libff::bigint<num_limbs>(x));

  mpz_t deg;
  mpz_init(deg);
  to_find_square_root.to_mpz(deg);

  mpz_t mode;
  mpz_init(mode);
  modulus.to_mpz(mode);

  mpz_powm(ret_val, x, deg, mode);

  mpz_clears(deg,mode,0);
}

std::string ElementZrToString(element_t el ) {
  std::string str = "1";
  if (element_item_count(el)) {
    str = "2";
  } else {
    mpz_t a;
    mpz_init(a);

    element_to_mpz(a, el);

    char arr[mpz_sizeinbase (a, 10) + 2];

    char * tmp = mpz_get_str(arr, 10, a);
    mpz_clear(a);

    str = tmp;
  }

  return str;
}

std::shared_ptr<std::vector<std::string>> ElementG1ToString(element_t el ) {
  std::vector<std::string> res_str;

  for ( int i = 0;  i < element_item_count(el); ++i) {
    res_str.push_back(ElementZrToString(element_item(el,i)));
  }
  
  return std::make_shared<std::vector<std::string>>(res_str);
}
