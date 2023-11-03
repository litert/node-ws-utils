/**
 * Copyright 2023 Angus.Fenying <i@fenying.net>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */``

const q = require('./build/Release/ws-utils.node');

const buf = Buffer.from('hello world');

const mask = Buffer.from('1234');

console.log('Before: ' + buf.toString('hex'));

q.mask(buf, mask, 2);

console.log('After:  ' + buf.toString('hex'));

q.mask(buf, mask, 2);

console.log('Again:  ' + buf.toString('hex'));
