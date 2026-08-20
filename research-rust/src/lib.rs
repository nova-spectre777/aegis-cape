#[derive(Clone, Debug, PartialEq)]
pub struct EnvelopeRange { pub min_delta: f64, pub max_delta: f64 }
pub fn expand(range: Option<EnvelopeRange>, value: f64) -> EnvelopeRange {
    match range { Some(r)=>EnvelopeRange{min_delta:r.min_delta.min(value),max_delta:r.max_delta.max(value)}, None=>EnvelopeRange{min_delta:value,max_delta:value} }
}
